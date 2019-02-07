#include "application.h"
#include "utils.h"
#include "image.h"

int mode = 0, count = 0;

Image framebuffer(800, 800);

Vector2 origin, end, vertex;

int lineInfo[800][1][1] = {};

struct sCelda { int minx, maxx; };

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	// initialize attributes

	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 

	// things create here cannot access opengl

	int w, h;

	SDL_GetWindowSize(window, &w, &h);

	this->window_width = w;

	this->window_height = h;

	this->keystate = SDL_GetKeyboardState(NULL);

}

//Here we have already GL working, so we can create meshes and textures

void Application::init(void)
{
	std::cout << "initiating app..." << std::endl;
	//here add your init stuff
}

// Draw a line using DDA Algorithm

void drawLine(int x0, int y0, int x1, int y1, Color c) 
{
	float	steps,

			dx = x1 - x0, // difference of x

			dy = y1 - y0, // difference of y

			// to see if the lines are going down or up (negative of positive)

			x = x0 + sgn(x0)*0.5,

			y = y0 + sgn(x0)*0.5;

	// calculate the number of iterations to paint the pixels
	if (abs(dx) >= abs(dy)) steps = abs(dx); else steps = abs(dy);

	float	Xincr = dx / steps, // increment for x in each pixel
		
			Yincr = dy / steps; // increment for y in each pixel

	for (int v = 0; v <= steps; v++)
	{
		framebuffer.setPixelSafe(floor(x), floor(y), c);

		x = x + Xincr; // paint each pixel every Xincr

		y = y + Yincr; // paint each pixel every Yincr
	}
}

// Draw a line using DDA Algorithm filling the table

void drawLineFillingTable(int x0, int y0, int x1, int y1, Color c, std::vector<sCelda> &table) 
{
	float	steps,

			dx = x1 - x0, // difference of x

			dy = y1 - y0, // difference of y

			// to see if the lines are going down or up (negative of positive)

			x = x0 + sgn(x0)*0.5,

			y = y0 + sgn(x0)*0.5;

	// calculate the number of iterations to paint the pixels
	if (abs(dx) >= abs(dy)) steps = abs(dx); else steps = abs(dy);

	float	Xincr = dx / steps, // increment for x in each pixel

			Yincr = dy / steps; // increment for y in each pixel

	for (int v = 0; v <= steps; v++)
	{
		framebuffer.setPixelSafe(x, y, c);

		if (x < table[y].minx) table[y].minx = x;

		if (x > table[y].maxx) table[y].maxx = x;

		x = x + Xincr; // paint each pixel every Xincr

		y = y + Yincr; // paint each pixel every Yincr
	}
}

// Draw a circle given position and radious

void drawCircle(Image* img, int x, int y, int r, Color c, bool fill) 
{
	int x1 = 0, y1 = r, v = 1 - r;

	while (y1 > x1) 
	{
		if (v < 0) 
		{
			v = v + 2 * x1 + 3;

			x1++;
		}

		else 
		{
			v = v + 2 * (x1 - y1) + 5;

			x1++;

			y1--;
		}

		if (fill)
		{
			drawLine(x - r, y, x + r, y, c);

			drawLine(x - x1, y + y1, x + x1, y + y1, c);

			drawLine(x + x1, y - y1, x - x1, y - y1, c);

			drawLine(x - y1, y + x1, x + y1, y + x1, c);

			drawLine(x + y1, y - x1, x - y1, y - x1, c);
		}

		else // Solve the problem of drawing in each octant
		{
			img->setPixelSafe(x + x1, y + y1, c);

			img->setPixelSafe(x - x1, y + y1, c);

			img->setPixelSafe(x - x1, y - y1, c);

			img->setPixelSafe(x + x1, y - y1, c);

			img->setPixelSafe(x + y1, y + x1, c);

			img->setPixelSafe(x - y1, y + x1, c);

			img->setPixelSafe(x - y1, y - x1, c);

			img->setPixelSafe(x + y1, y - x1, c);
		}
	}
}

// Draw a triangle given 3 dots

void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color c, bool fill)
{
	if (!fill) // Draw the triangle by simply drawing three lines
	{
		drawLine(x0, y0, x1, y1, c);

		drawLine(x1, y1, x2, y2, c);

		drawLine(x2, y2, x0, y0, c);
	}

	else 
	{
		std::vector<sCelda> table;

		table.resize(framebuffer.height);

		for (int i = 0; i < table.size(); i++) // inicializar tabla
		{
			table[i].minx = 1000000; // very big number

			table[i].maxx = -1000000; // very small number
		}

		drawLineFillingTable(x0, y0, x1, y1, c, table);

		drawLineFillingTable(x1, y1, x2, y2, c, table);

		drawLineFillingTable(x2, y2, x0, y0, c, table);

		for (int j = 0; j < table.size(); j++)
			if (table[j].minx < table[j].maxx) drawLine(table[j].minx, j, table[j].maxx, j, c);
	}
}

//render one frame

void Application::render(void)
{
	if (mode == 1) 
	{
		showImage(&framebuffer);
	}

	else if (mode == 2) 
	{
		showImage(&framebuffer);
	}

	else if (mode == 3) 
	{
		showImage(&framebuffer);
	}

	else if (mode == 4) 
	{
		showImage(&framebuffer);
	}

	else if (mode == 5) 
	{
		showImage(&framebuffer);
	}

	else 
	{
		framebuffer.fill(Color::BLACK);

		showImage(&framebuffer);
	}
}

void Application::update(double seconds_elapsed) // called after render
{
	// to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode

	if (keystate[SDL_SCANCODE_SPACE]) // if key space is pressed -- Clean
	{
		mode = 0;
	}

	if (keystate[SDL_SCANCODE_1]) // if key 1 is pressed -- Draw Line
	{
		mode = 1;
	}

	if (keystate[SDL_SCANCODE_2]) // if key 2 is pressed -- Draw Circle
	{
		mode = 2;
	}

	if (keystate[SDL_SCANCODE_3]) // if key 3 is pressed -- Draw Filled circle
	{
		mode = 3;
	}

	if (keystate[SDL_SCANCODE_4]) // if key 4 is pressed -- Draw Triangle
	{
		mode = 4;
	}

	if (keystate[SDL_SCANCODE_5]) // if key 5 is pressed -- Draw Filled Triangle
	{
		mode = 5;
	}
}

void Application::onKeyDown(SDL_KeyboardEvent event)
{
	// to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode

	switch (event.keysym.scancode)
	{
		case SDL_SCANCODE_ESCAPE:

			exit(0);

			break; //ESC key, kill the app
	}

}

void Application::onKeyUp(SDL_KeyboardEvent event) { }

void Application::onMouseButtonDown(SDL_MouseButtonEvent event) { }

void Application::onMouseButtonUp(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT) 
	{
		if (count == 0) origin = mouse_position;

		if (mode == 1) // Draw Line mode
		{
			if (count == 1) 
			{
				end = mouse_position;

				drawLine(origin.x, origin.y, end.x, end.y, Color::RED);

				count = -1;
			}

			count++;
		}

		if (mode == 2) // Draw circle mode
		{
			if (count == 1) 
			{
				end = mouse_position;

				int r = sqrt(pow(end.x - origin.x, 2) + pow(end.y - origin.y, 2));

				drawCircle(&framebuffer, origin.x, origin.y, r, Color::BLUE, FALSE);

				count = -1;
			}

			count++;
		}

		if (mode == 3) // Draw Filled circle mode
		{
			if (count == 1)
			{
				end = mouse_position;

				int r = sqrt(pow(end.x - origin.x, 2) + pow(end.y - origin.y, 2));

				drawCircle(&framebuffer, origin.x, origin.y, r, Color::GREEN, TRUE);

				count = -1;
			}

			count++;
		}

		if (mode == 4) // Draw Triangle mode
		{
			if (count == 1) end = mouse_position;

			else if (count == 2) 
			{
				vertex = mouse_position;

				drawTriangle(origin.x, origin.y, end.x, end.y, vertex.x, vertex.y, Color::YELLOW, FALSE);

				count = -1;
			}

			count++;
		}

		if (mode == 5) // Draw Filled Triangle mode
		{
			if (count == 1) end = mouse_position;

			else if (count == 2)
			{
				vertex = mouse_position;

				drawTriangle(origin.x, origin.y, end.x, end.y, vertex.x, vertex.y, Color::PURPLE, TRUE);

				count = -1;
			}

			count++;
		}
	}
}

// when the app starts

void Application::start()
{
	std::cout << "launching loop..." << std::endl;

	launchLoop(this);
}
