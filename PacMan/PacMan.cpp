    #include "stdafx.h"
    #include <vector>
    #include <algorithm>
    #include <Windows.h>
    #include <cmath>
    #include <iostream>
    #include <string>
    #include <sstream>
    #include <fstream>
     
    #define GetWindowStyle(hwnd) ((DWORD)GetWindowLong(hwnd, GWL_STYLE))
    #define GetWindowExStyle(hwnd) ((DWORD)GetWindowLong(hwnd, GWL_EXSTYLE))
     
     
    using namespace std;
    HINSTANCE hInst;
    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
    void CALLBACK Gracz(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
    void CALLBACK DuchA(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
    void CALLBACK DuchB(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
    char klawisz = VK_LEFT;
    char klawisz1 = VK_RIGHT;
    char klawisz2 = VK_RIGHT;
     
    string inttostr(int zmienna)
    {
		stringstream i;
		i << zmienna;
		return i.str();
    }
     
    bool szukaj(vector<POINT> wektor, POINT liczba)
    {
		for (int i = 0; i < wektor.size(); i++)
		{
			if ((wektor[i].x == liczba.x) && (wektor[i].y == liczba.y)) return true;
		}
    return false;
    }
     
    vector<POINT> szukaj_DEL(vector<POINT> wektor, POINT liczba)
    {
		for (int i = 0; i < wektor.size(); i++)
		{
			if ((wektor[i].x == liczba.x) && (wektor[i].y == liczba.y))
			{
				wektor.erase(wektor.begin() + i);
			}
		}
    return wektor;
    }
     
    bool RejestrujKlase()
    {
		WNDCLASSEX wc;
		wc.style = CS_NOCLOSE;
		wc.hInstance = hInst;
		wc.lpszClassName = TEXT("Okno");
		wc.lpfnWndProc = WndProc;
		wc.style = CS_DBLCLKS;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.lpszMenuName = 0;
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.cbWndExtra = 0;
		wc.cbClsExtra = 0;
     
		if (RegisterClassEx(&wc) == 0) return false;

		return true;
    }
     
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR lStart, INT nShow)
    {
		RejestrujKlase();
		HWND Okno = CreateWindowEx(0, TEXT("Okno"), TEXT("Pacman"), WS_OVERLAPPEDWINDOW & ~WS_MINIMIZEBOX, 50, 50, 700, 450, 0, 0, hInst, 0);
		ShowWindow(Okno, nShow);
     
		UINT G1 = SetTimer(Okno, 1, 200, &Gracz);
		UINT D1 = SetTimer(Okno, 2, 500, &DuchA);
		UINT D2 = SetTimer(Okno, 3, 500, &DuchB);
		MSG msgs;
		while (GetMessage(&msgs, 0, 0, 0))
		{
			TranslateMessage(&msgs);
			DispatchMessage(&msgs);
		}
     
		return msgs.wParam;
    }
    POINT postac, duch1, duch2;
    int szer, wys, linia = 0, kolumna = 0, wiersze = 1, kolumny = 0;
    bool warunek=true;
    vector <POINT> tablica;
    vector <POINT> kropki;
     
    void CALLBACK Gracz(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
	{
		RECT rect;
		POINT temp;
		temp.x = postac.y;
		temp.y = postac.x;
     
		HDC hdc = GetDC(hWnd);
		HBRUSH brush = CreateSolidBrush(0xFFFFFF);
		HPEN pen = CreatePen(PS_SOLID, 1, 0xFFFFFF);
		SelectObject(hdc, brush);
		SelectObject(hdc, pen);
     
		if (klawisz == VK_LEFT) 
		{
			POINT temp2;
			temp2.x = postac.x - 1;
			temp2.y = postac.y;
			if (!szukaj(tablica, temp2))
			{
				postac.x--;
				kropki = szukaj_DEL(kropki, temp2);
				rect.top = (temp.x - 1)*wys;
				rect.bottom = (temp.x + 1)*wys + wys;
				rect.left = (temp.y - 1)*szer;
				rect.right = (temp.y + 1)*szer + szer;
				InvalidateRect(hWnd, &rect, 1);
			}
		}
     
		if (klawisz == VK_RIGHT) 
		{
			POINT temp2;
			temp2.x = postac.x + 1;
			temp2.y = postac.y;
			if (!szukaj(tablica, temp2))
			{
				postac.x++;
				kropki = szukaj_DEL(kropki, temp2);
				rect.top = (temp.x - 1)*wys;
				rect.bottom = (temp.x + 1)*wys + wys;
				rect.left = (temp.y - 1)*szer;
				rect.right = (temp.y + 1)*szer + szer;
				InvalidateRect(hWnd, &rect, 1);
			}
		}
     
		if (klawisz == VK_UP) 
		{
			POINT temp2;
			temp2.x = postac.x;
			temp2.y = postac.y-1;
			if (!szukaj(tablica, temp2))
			{
				postac.y--;
				kropki = szukaj_DEL(kropki, temp2);
				rect.top = (temp.x - 1)*wys;
				rect.bottom = (temp.x + 1)*wys + wys;
				rect.left = (temp.y - 1)*szer;
				rect.right = (temp.y + 1)*szer + szer;
				InvalidateRect(hWnd, &rect, 1);
			}
		}
     
		if (klawisz == VK_DOWN) 
		{
			POINT temp2;
			temp2.x = postac.x;
			temp2.y = postac.y+1;
			if (!szukaj(tablica, temp2))
			{
				postac.y++;
				kropki = szukaj_DEL(kropki, temp2);
				rect.top = (temp.x - 1)*wys;
				rect.bottom = (temp.x + 1)*wys + wys;
				rect.left = (temp.y - 1)*szer;
				rect.right = (temp.y + 1)*szer + szer;
				InvalidateRect(hWnd, &rect, 1);
			}
		}
     
		if (kropki.size() == 0)
		{
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);
			MessageBox(hWnd, TEXT("Wygra³eœ!"), TEXT("KONIEC GRY"), MB_OK);
		}
    }
     
    void CALLBACK DuchA(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
	{
		RECT rect;
		POINT temp;
		temp.x = duch1.y;
		temp.y = duch1.x;
     
		HDC hdc = GetDC(hWnd);
		HBRUSH brush = CreateSolidBrush(0xFFFFFF);
		HPEN pen = CreatePen(PS_SOLID, 1, 0xFFFFFF);
		SelectObject(hdc, brush);
		SelectObject(hdc, pen);
     
		if (klawisz1 == VK_LEFT) 
		{
			POINT temp2;
			temp2.x = duch1.x - 1;
			temp2.y = duch1.y;
			if (!szukaj(tablica, temp2))
			duch1.x--;
			else
			klawisz1 = VK_UP;
			rect.top = (temp.x - 1)*wys;
			rect.bottom = (temp.x + 1)*wys + wys;
			rect.left = (temp.y - 1)*szer;
			rect.right = (temp.y + 1)*szer + szer;
			InvalidateRect(hWnd, &rect, 1);
		}
     
		if (klawisz1 == VK_RIGHT) 
		{
			POINT temp2;
			temp2.x = duch1.x + 1;
			temp2.y = duch1.y;
			if (!szukaj(tablica, temp2))
				duch1.x++;
			else
				klawisz1 = VK_DOWN;
			rect.top = (temp.x - 1)*wys;
			rect.bottom = (temp.x + 1)*wys + wys;
			rect.left = (temp.y - 1)*szer;
			rect.right = (temp.y + 1)*szer + szer;
			InvalidateRect(hWnd, &rect, 1);
		}
     
		if (klawisz1 == VK_UP) 
		{
			POINT temp2;
			temp2.x = duch1.x;
			temp2.y = duch1.y - 1;
			if (!szukaj(tablica, temp2))
				duch1.y--;
			else
				klawisz1 = VK_RIGHT;
			rect.top = (temp.x - 1)*wys;
			rect.bottom = (temp.x + 1)*wys + wys;
			rect.left = (temp.y - 1)*szer;
			rect.right = (temp.y + 1)*szer + szer;
			InvalidateRect(hWnd, &rect, 1);
		}
     
		if (klawisz1 == VK_DOWN) 
		{
			POINT temp2;
			temp2.x = duch1.x;
			temp2.y = duch1.y + 1;
			if (!szukaj(tablica, temp2))
				duch1.y++;
			else
				klawisz1 = VK_LEFT;
			rect.top = (temp.x - 1)*wys;
			rect.bottom = (temp.x + 1)*wys + wys;
			rect.left = (temp.y - 1)*szer;
			rect.right = (temp.y + 1)*szer + szer;
			InvalidateRect(hWnd, &rect, 1);
		}
     
		if ((duch1.x == postac.x) && (duch1.y == postac.y))
		{
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);
			MessageBox(hWnd, TEXT("Przegra³eœ!"), TEXT("KONIEC GRY"), MB_OK);
		}
    }
     
    void CALLBACK DuchB(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
	{
		RECT rect;
		POINT temp;
		temp.x = duch2.y;
		temp.y = duch2.x;
     
		HDC hdc = GetDC(hWnd);
		HBRUSH brush = CreateSolidBrush(0xFFFFFF);
		HPEN pen = CreatePen(PS_SOLID, 1, 0xFFFFFF);
		SelectObject(hdc, brush);
		SelectObject(hdc, pen);
     
		if (klawisz2 == VK_LEFT) 
		{
			POINT temp2;
			temp2.x = duch2.x - 1;
			temp2.y = duch2.y;
			if (!szukaj(tablica, temp2))
			duch2.x--;
			else
			klawisz2 = VK_UP;
			rect.top = (temp.x - 1)*wys;
			rect.bottom = (temp.x + 1)*wys + wys;
			rect.left = (temp.y - 1)*szer;
			rect.right = (temp.y + 1)*szer + szer;
			InvalidateRect(hWnd, &rect, 1);
		}
     
		if (klawisz2 == VK_RIGHT) 
		{
			POINT temp2;
			temp2.x = duch2.x + 1;
			temp2.y = duch2.y;
			if (!szukaj(tablica, temp2))
			duch2.x++;
			else
			klawisz2 = VK_DOWN;
			rect.top = (temp.x - 1)*wys;
			rect.bottom = (temp.x + 1)*wys + wys;
			rect.left = (temp.y - 1)*szer;
			rect.right = (temp.y + 1)*szer + szer;
			InvalidateRect(hWnd, &rect, 1);
		}
     
		if (klawisz2 == VK_UP) 
		{
			POINT temp2;
			temp2.x = duch2.x;
			temp2.y = duch2.y - 1;
			if (!szukaj(tablica, temp2))
			duch2.y--;
			else
			klawisz2 = VK_RIGHT;
			rect.top = (temp.x - 1)*wys;
			rect.bottom = (temp.x + 1)*wys + wys;
			rect.left = (temp.y - 1)*szer;
			rect.right = (temp.y + 1)*szer + szer;
			InvalidateRect(hWnd, &rect, 1);
		}
     
		if (klawisz2 == VK_DOWN) 
		{
			POINT temp2;
			temp2.x = duch2.x;
			temp2.y = duch2.y + 1;
			if (!szukaj(tablica, temp2))
			duch2.y++;
			else
			klawisz2 = VK_LEFT;
			rect.top = (temp.x - 1)*wys;
			rect.bottom = (temp.x + 1)*wys + wys;
			rect.left = (temp.y - 1)*szer;
			rect.right = (temp.y + 1)*szer + szer;
			InvalidateRect(hWnd, &rect, 1);
		}
     
		if ((duch2.x == postac.x) && (duch2.y == postac.y))
		{
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);
			MessageBox(hWnd, TEXT("Przegra³eœ!"), TEXT("KONIEC GRY"), MB_OK);
		}
    }
     
    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wPar, LPARAM lPar)
	{
		switch (msg)
		{
			case WM_CREATE:
			{
				string a, znak;
				ifstream mapa("mapa.txt");
     
				do
				{
					znak = mapa.get();
					a += znak;
					if ((znak != "\n") && (warunek==true)) kolumny++;
					if (znak == "x")
					{
						POINT temp;
						temp.x = kolumna;
						temp.y = linia;
						tablica.push_back(temp);
					}
					else if (znak == ".")
					{
						POINT temp;
						temp.x = kolumna;
						temp.y = linia;
						kropki.push_back(temp);	
					}
					else if (znak == "o")
					{
						postac.x = kolumna;
						postac.y = linia;
					}
					else if (znak == "1")
					{
						duch1.x = kolumna;
						duch1.y = linia;
					}
					else if (znak == "2")
					{
						duch2.x = kolumna;
						duch2.y = linia;
					}
					else if (znak == "\n")
					{
						kolumna = -1;
						linia++;
						wiersze++;
						warunek = false;
					}
					kolumna++;
				} 
				while (!mapa.eof());
     
				RECT rect;
				rect.top = 100;
				rect.bottom = 40 * wiersze;;
				rect.left = 100;
				rect.right = 40*kolumny;
				AdjustWindowRectEx(&rect, GetWindowStyle(hwnd), GetMenu(hwnd) != NULL, GetWindowExStyle(hwnd));
     
				SetWindowPos(hwnd, 0, rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW);
				break;
			}
			case WM_KEYDOWN:
			{
				if (LOWORD(wPar) == VK_UP) klawisz=VK_UP;
				if (LOWORD(wPar) == VK_DOWN) klawisz = VK_DOWN;
				if (LOWORD(wPar) == VK_LEFT) klawisz = VK_LEFT;
				if (LOWORD(wPar) == VK_RIGHT) klawisz = VK_RIGHT;
     
				break;
			}
			case WM_PAINT:
			{
				RECT rect;
				GetClientRect(hwnd, &rect);
				int width = rect.right - rect.left;
				int height = rect.bottom - rect.top;
				szer = (width / kolumny);
				wys = (height / wiersze);
				PAINTSTRUCT paint;
				HDC hdc = BeginPaint(hwnd, &paint);
				HBRUSH brush = CreateSolidBrush(0x2f3232);
				HGDIOBJ brush_temp = SelectObject(hdc, brush);
				for (int i = 0; i < tablica.size(); i++)
				Rectangle(hdc, tablica[i].x*szer, tablica[i].y*wys, (tablica[i].x*szer) + szer, (tablica[i].y*wys) + wys);
				brush = CreateSolidBrush(0x00FFFF);
				SelectObject(hdc, brush);
				for (int i = 0; i < kropki.size(); i++)
				Ellipse(hdc, (kropki[i].x*szer) + (0.75*szer), (kropki[i].y*wys) + (0.75*wys), (kropki[i].x*szer) + szer - (0.75*szer), (kropki[i].y*wys) + wys - (0.75*wys));
     
				brush = CreateSolidBrush(0x0000FF);
				SelectObject(hdc, brush);
				//Ellipse(hdc, postac.x*szer, postac.y*wys, (postac.x*szer) + szer, (postac.y*wys) + wys);
     
				brush = CreateSolidBrush(0x00A5FF);
				SelectObject(hdc, brush);
				Ellipse(hdc, duch1.x*szer, duch1.y*wys, (duch1.x*szer) + szer, (duch1.y*wys) + wys);
     
				brush = CreateSolidBrush(0xFF00FF);
				SelectObject(hdc, brush);
				Ellipse(hdc, duch2.x*szer, duch2.y*wys, (duch2.x*szer) + szer, (duch2.y*wys) + wys);
     
				SelectObject(hdc, brush_temp);
     
				DeleteObject(brush);
				DeleteObject(brush_temp);
     
				EndPaint(hwnd, &paint);
     
				break;
			}
     
			case WM_SIZE:
			RECT okno;
			GetClientRect(hwnd, &okno);
			InvalidateRect(hwnd, &okno, 1);
			break;
     
			case WM_DESTROY:
			PostQuitMessage(0);
			break;
			default:
			return DefWindowProc(hwnd, msg, wPar, lPar);
		}
		return 0;
    }