#ifndef _WRESIZE_H
#define _WRESIZE_H

//included in includes.h

/*
   wResize.h
   Copyright (C) 2017-2018 James Gavin
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.
   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:
   1. The origin of this source code must not be misrepresented; you must not
	  claim that you wrote the original source code. If you use this source code
	  in a product, an acknowledgment in the product documentation would be
	  appreciated but is not required.
   2. Altered source versions must be plainly marked as such, and must not be
	  misrepresented as being the original source code.
   3. This notice may not be removed or altered from any source distribution.
   James Gavin dragonkings@gmail.com
*/

struct AnchorInformation //consider flaging
{
	bool Top;
	bool Right;
	bool Bottom;
	bool Left;
};

struct RectPercent
{
	float x;
	float y;
	float width;
	float height;
	float fromtheright;
	float fromthebottom;
	float reverse_x;
	float reverse_y;
};
struct WindowInformation
{
	HWND ChildWindow;
	HWND ParentWindow;
	RECT ParentRect;
	WINDOWPLACEMENT pChildPlace; //RECT ChildRect;
	RectPercent pChildRect;			/* This structure should never change its values after Init */

	float x, y;						/* Our math here is going to fuck up at some point, MoveWindow uses (int) so does SetWindowPos */
	float height, width;
	int ParentWidth, ParentHeight = 0;

	AnchorInformation Anchors;

	void UpdateParent()
	{
		GetWindowRect(ParentWindow, &ParentRect);
		ParentWidth = ParentRect.right - ParentRect.left;
		ParentHeight = ParentRect.bottom - ParentRect.top;
	}

	void SetWindow(const HWND hParentWindow, const HWND hChildWindow, const bool b_top, const bool b_bottom, const bool b_left, const bool b_right)
	{
		ParentWindow = hParentWindow;
		UpdateParent();

		ChildWindow = hChildWindow;
		GetWindowPlacement(ChildWindow, &pChildPlace); //GetWindowRect(ChildWindow, &ChildRect); RECT here gives false information

		/* Get child x and y positions */
		x = pChildPlace.rcNormalPosition.left; //x = ChildRect.left; //.RC saying its at 7, 7.................................
		y = pChildPlace.rcNormalPosition.top; //y = ChildRect.top;
		/* Get height and width */
		height = pChildPlace.rcNormalPosition.bottom - pChildPlace.rcNormalPosition.top; //height = ChildRect.bottom - ChildRect.top;
		width = pChildPlace.rcNormalPosition.right - pChildPlace.rcNormalPosition.left; //width = ChildRect.right - ChildRect.left;

		//Anchors
		Anchors.Top = b_top;
		Anchors.Bottom = b_bottom;
		Anchors.Left = b_left;
		Anchors.Right = b_right;

		//SetPercentages
		SetCurrentPercentages();
	}

	void SetCurrentPercentages()
	{
		pChildRect.x = x / (float)ParentWidth;
		pChildRect.y = y / (float)ParentHeight;
		pChildRect.height = height / (float)ParentHeight;
		pChildRect.width = width / (float)ParentWidth;
		pChildRect.fromtheright = (float)ParentWidth - x;
		pChildRect.fromthebottom = (float)ParentHeight - y;
		pChildRect.reverse_x = (((float)ParentWidth - x) - width);
		pChildRect.reverse_y = (((float)ParentHeight - y) - height);
	}

	/*
		[done]	Top							= (Height = Locked)		(Width = Locked)		(x and y = Locked)
		[done]	Right						= (Height = Locked)		(Width = Locked)		(x = based on width, y = Locked) (x is locked at how far it is from the right)
		[done]	Bottom						= (Height = Locked)		(Width = Locked)		(x = Locked, y = based on height) (y is locked at how far it is from the bottom)
		[done]	Left						= (Height = Locked)		(Width = Locked)		(x and y = Locked)
		[done]	Top + Bottom				= (Height = Resizing)	(Width = Locked)		(x and y = Locked)
		[done]	Left + Right				= (Height = Locked)		(Width = Resizing)		(x and y = Locked) [x = 0->x] [y = ((pWidth - x) - cWidth) (remaining blank space between right border and right side of the client window)
		[done]	Right + Top + Bottom		= (Height = Resizing)	(Width = Locked)		(x = Based on width, y = Locked)
		[done]	Left + Top + Bottom			= (Height = Resizing)	(Width = Locked)		(x = Locked, y = Locked)					[same as (top + bottom)]
		[done]	Top + Left + Right + Bottom	= (Height = Resizing)	(Width = Resizing)		(x and y = Locked)
		[done]	Left + Top + Right			= (Height = Locked)		(Width = Resizing)		(x and y = Locked)							[same as (right + left)]
		[done]	Left + Bottom + Right		= (Height = Locked)		(Width = Resizing)		(x = Locked, y = Based on height)
		[done]	Left + Top					= (Height = Locked)		(Width = Locked)		(x and y = Locked)							[all values have no changes ignore]
		[done]	Right + Top					= (Height = Locked)		(Width = Locked)		(x = based on width, y = locked)			[same as (right only)]
		[done]	Left + Bottom				= (Height = Locked)		(Width = Locked)		(y = based on height, x = locked)			[same as (bottom only)]
		[done]	Right + Bottom				= (Height = Locked)		(Width = Locked)		(y = based on height, x = based on width)
								___________________________________________________________________________________
		diag: 1: (left + right) || <- x -> | <- client width  -> | <- space remaining until the right border  -> ||
		diag: 2: (top + bottom) || <- y -> | <- client height -> | <- space remaining until the bottom border -> ||
								||_________|_____________________|_______________________________________________||
							1: new width (height same math just x is y and width is height)
								constant reverse_x = parent_width - (x + client_width)
								n_width = (parent_width - x) - ((parent_width - (parent_width - reverse_x))
			Reminder: [done]
				Where resizing is concerned, Height and Width values can not go neg. (apparently x and y can though)
	*/

	void DoMoveResize()
	{
		//GetWindowRect GetClientRect
		UpdateParent();

		//Now do math based on anchors + our percentages
		//No anchors were set, no changes
		if (Anchors.Top == false && Anchors.Bottom == false && Anchors.Left == false && Anchors.Right == false)
		{
			return;
		}
		//Top							= (Height = Locked)		(Width = Locked)		(x and y = Locked)
		if (Anchors.Top == true && Anchors.Bottom == false && Anchors.Left == false && Anchors.Right == false)
		{
			return;
		}
		//Right						= (Height = Locked)		(Width = Locked)		(x = based on width, y = Locked)
		if (Anchors.Top == false && Anchors.Bottom == false && Anchors.Left == false && Anchors.Right == true)
		{
			//	: SetWindowPos(hWnd, NULL, X, Y, nWidth, nHeight, SWP_NOZORDER | (bool)bRepaint * SWP_NOREDRAW))
			//Only x is updated.
			x = ParentWidth - pChildRect.fromtheright;// ParentRect.right * pChildRect.x;
			SetWindowPos(ChildWindow, NULL, x, y, width, height, SWP_NOZORDER);
			return;
		}
		//Bottom						= (Height = Locked)		(Width = Locked)		(x = Locked, y = based on height)
		if (Anchors.Top == false && Anchors.Bottom == true && Anchors.Left == false && Anchors.Right == false)
		{
			//Only y is updated.
			y = ParentHeight - pChildRect.fromthebottom;// ParentRect.right * pChildRect.x;
			SetWindowPos(ChildWindow, NULL, x, y, width, height, SWP_NOZORDER);
			return;
		}
		//Left						= (Height = Locked)		(Width = Locked)		(x and y = Locked)
		if (Anchors.Top == false && Anchors.Bottom == false && Anchors.Left == true && Anchors.Right == false)
		{
			return;
		}
		//Left + Top						= (Height = Locked)		(Width = Locked)		(x and y = Locked)
		if (Anchors.Top == true && Anchors.Bottom == false && Anchors.Left == true && Anchors.Right == false)
		{
			return;
		}
		//Right + Bottom				= (Height = Locked)		(Width = Locked)		(y = based on height, x = based on width)
		if (Anchors.Top == false && Anchors.Bottom == true && Anchors.Left == false && Anchors.Right == true)
		{
			//Only y is updated.
			x = ParentWidth - pChildRect.fromtheright;// ParentRect.right * pChildRect.x;
			y = ParentHeight - pChildRect.fromthebottom;// ParentRect.right * pChildRect.x;
			SetWindowPos(ChildWindow, NULL, x, y, width, height, SWP_NOZORDER);
			return;
		}
		//Left + Bottom				= (Height = Locked)		(Width = Locked)		(y = based on height, x = locked)		##### Same as Bottom only #####
		if (Anchors.Top == false && Anchors.Bottom == true && Anchors.Left == true && Anchors.Right == false)
		{
			//Only y is updated.
			y = ParentHeight - pChildRect.fromthebottom;// ParentRect.right * pChildRect.x;
			SetWindowPos(ChildWindow, NULL, x, y, width, height, SWP_NOZORDER);
			return;
		}
		//Right + Top					= (Height = Locked)		(Width = Locked)		(x = based on width, y = locked)			[same as (right only)]
		if (Anchors.Top == true && Anchors.Bottom == false && Anchors.Left == false && Anchors.Right == true)
		{
			//Only x is updated.
			x = ParentWidth - pChildRect.fromtheright;// ParentRect.right * pChildRect.x;
			SetWindowPos(ChildWindow, NULL, x, y, width, height, SWP_NOZORDER);
			return;
		}
		//Left + Right				= (Height = Locked)		(Width = Resizing)		(x and y = Locked) [x = 0->x] [y = ((pWidth - x) - cWidth) (remaining blank space between right border and right side of the client window)
		if (Anchors.Top == false && Anchors.Bottom == false && Anchors.Left == true && Anchors.Right == true)
		{
			//only width is updated.
			width = ((float)ParentWidth - x) - (((float)ParentWidth) - ((float)ParentWidth - pChildRect.reverse_x));// (float)ParentRect.right - pChildRect.reverse_x;
			if (width < 0) { width = 0; }
			SetWindowPos(ChildWindow, NULL, x, y, width, height, SWP_NOZORDER);
			return;
		}
		//Left + Top + Right			= (Height = Locked)		(Width = Resizing)		(x and y = Locked)							[same as (right + left)]
		if (Anchors.Top == true && Anchors.Bottom == false && Anchors.Left == true && Anchors.Right == true)
		{
			//only width is updated.
			width = ((float)ParentWidth - x) - (((float)ParentWidth) - ((float)ParentWidth - pChildRect.reverse_x));// (float)ParentRect.right - pChildRect.reverse_x;
			if (width < 0) { width = 0; }
			SetWindowPos(ChildWindow, NULL, x, y, width, height, SWP_NOZORDER);
			return;
		}
		//Left + Bottom + Right		= (Height = Locked)		(Width = Resizing)		(x = Locked, y = Based on height)
		if (Anchors.Top == false && Anchors.Bottom == true && Anchors.Left == true && Anchors.Right == true)
		{
			//y and width is updated.
			y = (float)ParentHeight - pChildRect.fromthebottom;// ParentRect.right * pChildRect.x;
			width = ((float)ParentWidth - x) - (((float)ParentWidth) - ((float)ParentWidth - pChildRect.reverse_x));// (float)ParentRect.right - pChildRect.reverse_x;
			if (width < 0) { width = 0; }
			SetWindowPos(ChildWindow, NULL, x, y, width, height, SWP_NOZORDER);
			return;
		}
		//Top + Bottom				= (Height = Resizing)	(Width = Locked)		(x and y = Locked)
		if (Anchors.Top == true && Anchors.Bottom == true && Anchors.Left == false && Anchors.Right == false)
		{
			//only height is updated.
			height = ((float)ParentHeight - y) - (((float)ParentHeight) - ((float)ParentHeight - pChildRect.reverse_y));// (float)ParentRect.right - pChildRect.reverse_x;
			if (height < 0) { height = 0; }
			SetWindowPos(ChildWindow, NULL, x, y, width, height, SWP_NOZORDER);
			return;
		}
		//Right + Top + Bottom		= (Height = Resizing)	(Width = Locked)		(x = Based on width, y = Locked)
		if (Anchors.Top == true && Anchors.Bottom == true && Anchors.Left == false && Anchors.Right == true)
		{
			//x, height is updated.
			x = ParentWidth - pChildRect.fromtheright;// ParentRect.right * pChildRect.x;
			height = ((float)ParentHeight - y) - (((float)ParentHeight) - ((float)ParentHeight - pChildRect.reverse_y));// (float)ParentRect.right - pChildRect.reverse_x;
			if (height < 0) { height = 0; }
			SetWindowPos(ChildWindow, NULL, x, y, width, height, SWP_NOZORDER);
			return;
		}
		//Left + Top + Bottom				= (Height = Resizing)	(Width = Locked)		(x and y = Locked)
		if (Anchors.Top == true && Anchors.Bottom == true && Anchors.Left == true && Anchors.Right == false)
		{
			//only height is updated.
			height = ((float)ParentHeight - y) - (((float)ParentHeight) - ((float)ParentHeight - pChildRect.reverse_y));// (float)ParentRect.right - pChildRect.reverse_x;
			if (height < 0) { height = 0; }
			SetWindowPos(ChildWindow, NULL, x, y, width, height, SWP_NOZORDER);
			return;
		}
		//Top + Left + Right + Bottom	= (Height = Resizing)	(Width = Resizing)		(x and y = Locked)
		if (Anchors.Top == true && Anchors.Bottom == true && Anchors.Left == true && Anchors.Right == true)
		{
			//only height is updated.
			height = ((float)ParentHeight - y) - (((float)ParentHeight) - ((float)ParentHeight - pChildRect.reverse_y));// (float)ParentRect.right - pChildRect.reverse_x;
			if (height < 0) { height = 0; }
			width = ((float)ParentWidth - x) - (((float)ParentWidth) - ((float)ParentWidth - pChildRect.reverse_x));// (float)ParentRect.right - pChildRect.reverse_x;
			if (width < 0) { width = 0; }
			SetWindowPos(ChildWindow, NULL, x, y, width, height, SWP_NOZORDER);
			return;
		}
	}

};

class wResize
{
private:
	std::vector<WindowInformation> Windows;
public:

	//Only needed if you create menu via API
	void AddMenuHeight(const HWND hParentWindow)
	{
		//GetMenuBarInfo()
		int cy_border = GetSystemMetrics(SM_CYFRAME);

		int cy_caption = GetSystemMetrics(SM_CYCAPTION);

		RECT window_rect;

		GetWindowRect(hParentWindow, &window_rect);

		POINT client_top_left = { 0, 0 };

		ClientToScreen(hParentWindow, &client_top_left);

		int menu_height = client_top_left.y - window_rect.top - cy_caption - (cy_border * 2);

		int height, width = 0;
		height = window_rect.bottom - window_rect.top;
		height += menu_height;
		width = window_rect.right - window_rect.left;
		//add the height to the window now.
		SetWindowPos(hParentWindow, NULL, client_top_left.x, client_top_left.y, width, height, SWP_NOZORDER);
	}

	void AddWindow(WindowInformation WindowData)
	{
		Windows.push_back(WindowData);
	}

	void AddWindow(const HWND hParentWindow, const HWND hChildWindow, const bool b_top, const bool b_bottom, const bool b_left, const bool b_right)
	{
		WindowInformation WindowData;
		WindowData.SetWindow(hParentWindow, hChildWindow, b_top, b_bottom, b_left, b_right);
		AddWindow(WindowData);
	}

	bool ResizeWindows()
	{
		std::vector<WindowInformation>::iterator it;
		for (it = Windows.begin(); it != Windows.end(); it++)
		{
			it->DoMoveResize();
		}
		return TRUE;
	}
};


#endif
