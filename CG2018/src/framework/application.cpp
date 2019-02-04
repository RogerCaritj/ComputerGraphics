#include "application.h"
#include "utils.h"
#include "image.h"
#include <time.h>
#include <tuple>
#include <windows.h>

int modo = 0;
int changeRoute = 0;
float count = 0;
int size = 1000;
float r = rand();
int *arrayX = new int[size];
int *arrayY = new int[size];
int *randoms = new int[size];
int clicX = 0;
int clicY = 0;
int prev_state = 0;
Image framebuffer3(800, 600);
Image framebuffer4(800, 600);
Image framebuffer7(800, 600);

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	int w,h;
	SDL_GetWindowSize(window,&w,&h);

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
void bigerPixel(Image* img)
{
	int randomColor1 = (((frand()) * 255) % 255);
	int randomColor2 = (((frand()) * 255) % 255);
	int randomColor3 = (((frand()) * 255) % 255);
	for(int x = 380; x<420; x++)
		for (int y = 280; y < 320; y++) {
			img->setPixelSafe(x, y, Color(randomColor1, randomColor2, randomColor3)); //random color
		}
}
void spiral(Image* img, float x, float y) {
	float angle = 0.0f;

	// Space between the spirals
	int a = 2, b = 2;
	float x1, y1;
	for (int i = 0; i < 150; i = i++)
	{
		angle = 0.1 * i;
		x1 = (a + b * angle) * cos(angle);
		y1 = (a + b * angle) * sin(angle);
		img->setPixelSafe(x1 + x , y1 + y, Color(255, 255, 255));
	}
}

void circle(Image* img, int posX, int posY) {
	float radius1 = 100 * count; // radius for the big circle
	float radius2 = 50 * count; // radius for the small cirle

	for (int angle = 0; angle < 360; angle += 1) {
		// calculate x and y by using parametic formulas of each circle
		int x1 = (radius1 * cos(angle));
		int y1 = (radius1 * sin(angle));
		int x2 = (radius2 * cos(angle));
		int y2 = (radius2 * sin(angle));

		// moving cordinates toward center of the display for each circle
		int cx1 = posX + x1;
		int cy1 = posY + y1;
		int cx2 = posX + x2;
		int cy2 = posY + y2;
		
		// degradate the color until it disapears
		int colorChanging1 = 255 - count * 250;
		int colorChanging2 = 255 - (count - 0.15) * 200;

		if (colorChanging1 <= 0) {
			colorChanging1 = 0;
		}
		if (colorChanging2 <= 0) {
			colorChanging2 = 0;
		}

		// character which made the circle
		img->setPixelSafe(cx1, cy1, Color(colorChanging1, 0, 0));
		if (count > 0.15){
			img->setPixelSafe(cx2, cy2, Color(colorChanging2, 0, 0));
		}
	}
	count = count + 0.01;
}
void triangle(Image* img, int x, int y) {
	const int SIZE = 35;
	for (int y1 = 0; y1 <= SIZE; ++y1) {
		for (int x1 = 0; x1 <= SIZE * 2; ++x1) {
			if (abs(x1 - SIZE) < (y1 + 1)) {
				img->setPixelSafe(x1 + x, y1 + y, Color(255, 255, 255));
			}
		}
	}
}
void circleSimple(Image* img, int posX, int posY) {
	float radius = 25; // radius for the big circle

	for (int angle = 0; angle < 360; angle += 1) {
		// calculate x and y by using parametic formulas of each circle
		int x = (radius * cos(angle));
		int y = (radius * sin(angle));

		// moving cordinates toward center of the display for each circle
		int cx = posX + x;
		int cy = posY + y;

		// character which made the circle
		img->setPixelSafe(cx, cy, Color(255, 255, 255));
	}
}
void square(Image* img, int x, int y) {
	int size = 40;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			img->setPixelSafe(i + x, j + y, Color(255, 255, 255));
		}
	}
}
void drawForms(Image* img)
{
	circleSimple(img, 200, 200);
	circleSimple(img, 600, 400);
	spiral(img, 200, 300);
	spiral(img, 600, 300);
	triangle(img, 370, 170);
	triangle(img, 370, 370);
	square(img, 185, 365);
	square(img ,585,165);
}
void dividePixel(Image* img) {
	int randomColor1 = (((frand()) * 255) % 255);
	int randomColor2 = (((frand()) * 255) % 255);
	int randomColor3 = (((frand()) * 255) % 255);

		//Down left
		for (int x = 380; x < 400; x++)
			for (int y = 280; y < 300; y++) {
				if (changeRoute == 1) {
					for (int z = 180; z < 201; z++) {
						img->setPixelSafe(z + 20 + 40 * -sin(count + 1.45), y + 100*cos(3*count), Color(randomColor1, randomColor2, randomColor3)); //random color
					}
				}
				else {
					img->setPixelSafe(x - count * 40, y, Color(randomColor1, randomColor2, randomColor3)); //random color
				}
			}
		//Down right
		for (int x = 400; x < 420; x++)
			for (int y = 280; y < 300; y++) {
				if (changeRoute == 1) {
					for (int z = 80; z < 101; z++) {
						img->setPixelSafe(x, z + 20 + 40 * -sin(count + 1.45), Color(randomColor1, randomColor2, randomColor3)); //random color
					}
				}
				else {
					img->setPixelSafe(x, y - count * 40, Color(randomColor1, randomColor2, randomColor3)); //random color
				}
			}
		//Up left
		for (int x = 380; x < 400; x++)
			for (int y = 300; y < 320; y++) {
				if (changeRoute == 1) {
					for (int z = 480; z < 501; z++) {
						img->setPixelSafe(x, z + 20 + 40 * sin(count + 1.45), Color(randomColor1, randomColor2, randomColor3)); //random color
					}
				}
				else {
					img->setPixelSafe(x , y + count * 40, Color(randomColor1, randomColor2, randomColor3)); //random color
				}
			}
		//Up right
		for (int x = 400; x < 420; x++)
			for (int y = 300; y < 320; y++) {
				if (x + count * 40 > 600) {
					changeRoute = 1;
				}
				if (changeRoute == 1) {
					for (int z = 580; z < 601; z++) {
						img->setPixelSafe(z + 20 + 40 * sin(count + 1.45), y + 100*-cos(3 * count), Color(randomColor1, randomColor2, randomColor3)); //random color
					}
				}
				else {
					img->setPixelSafe(x + count * 40, y, Color(randomColor1, randomColor2, randomColor3)); //random color
				}
			}
		count = count + 0.05;
}

void drawSnow(Image* img) {
	for (int i = 0; i < size; i++) {
		int x1 = arrayX[i] + sin(count * (randoms[i] % 10 + 3)) * 20;
		int x2 = arrayX[i] + sin(count * (randoms[i] % 10 + 3)) * 20 + 1;
		int y1 = arrayY[i] - count * (arrayX[i] % 40) + 3;
		int y2 = arrayY[i] - count * (arrayX[i] % 40) + 3 + 1;
		if (y1 < 0) {
			y1 = y1 + 600;
			y2 = y2 + 600;
		}
		img->setPixelSafe(x1, y1 , Color(255, 255, 255));
		img->setPixelSafe(x2, y1, Color(255, 255, 255)); 
		img->setPixelSafe(x1, y2, Color(255, 255, 255)); 
		img->setPixelSafe(x2, y2, Color(255, 255, 255)); 
	}
	count = count + 0.001;
}

void altereImage(Image& framebuffer)
{
	for (unsigned int i = 1; i < framebuffer.width - 1; i += 1)
		for (unsigned int j = 1; j < framebuffer.height - 1; j += 1)
		{
			int b = framebuffer.getPixel(i, j).b +
				framebuffer.getPixel(i - 1, j).b +
				framebuffer.getPixel(i + 1, j).b +
				framebuffer.getPixel(i, j + 1).b +
				framebuffer.getPixel(i, j - 1).b +
				framebuffer.getPixel(i + 1, j + 1).b +
				framebuffer.getPixel(i + 1, j - 1).b +
				framebuffer.getPixel(i - 1, j + 1).b +
				framebuffer.getPixel(i - 1, j - 1).b,

				g = framebuffer.getPixel(i, j).g +
				framebuffer.getPixel(i - 1, j).g +
				framebuffer.getPixel(i + 1, j).g +
				framebuffer.getPixel(i, j + 1).g +
				framebuffer.getPixel(i, j - 1).g +
				framebuffer.getPixel(i + 1, j + 1).g +
				framebuffer.getPixel(i + 1, j - 1).g +
				framebuffer.getPixel(i - 1, j + 1).g +
				framebuffer.getPixel(i - 1, j - 1).g,

				r = framebuffer.getPixel(i, j).r +
				framebuffer.getPixel(i - 1, j).r +
				framebuffer.getPixel(i + 1, j).r +
				framebuffer.getPixel(i, j + 1).r +
				framebuffer.getPixel(i, j - 1).r +
				framebuffer.getPixel(i + 1, j + 1).r +
				framebuffer.getPixel(i + 1, j - 1).r +
				framebuffer.getPixel(i - 1, j + 1).r +
				framebuffer.getPixel(i - 1, j - 1).r;

			b /= 9.0; g /= 9.0; r /= 9.0;

			framebuffer.setPixel(i, j, Color(r, g, b));
		}
	//framebuffer.saveTGA("bubblesE.tga");
}

void drawImage(Image* img) {
	for (float i = 0; i < img->width; i++)
		for (float j = 0; j < img->height; j++)
		{
			//float a = i + sin(j*0.02 + count);
			//float b = j + sin(i*0.02 + count);
			Color c = img->getPixel(i, j);
			Color c1 = Color(0, 255, 0);
			Color c2 = Color(200,0,0);
			if(c.r > 200){
				img->setPixelSafe(i, j, c1);
			}
			if (c.g < 50 && c.r < 50 && c.b < 50) {
				img->setPixelSafe(i, j, c2);
			}
			//img->setPixelSafe(a, b, c);
		}
	count = count + 0.01;
}
void setBackgroundColor(Image& im, Color c)
{
	for (unsigned int x = 0; x < im.width; x++)
		for (unsigned int y = 0; y < im.height; y++)
			im.setPixel(x, y, c);
}
// only guaranteed to work on horizontal and vertical lines
void drawLine(Image& framebuffer, unsigned int xi, unsigned int yi, unsigned int xf, unsigned int yf, Color c)
{
	int i = 0, j = 0;

	while (xi + i != xf || yi + j != yf)
	{
		framebuffer.setPixel(xi + i, yi + j, c);

		if (xf > xi + i) i++; else if (xf < xi + i) i--;
		if (yf > yi + j) j++; else if (yf < yi + j) j--;
	}
}

std::vector< std::tuple< unsigned int, unsigned int > > getDrawablePixels(Image& framebuffer, unsigned int amount, unsigned int length)
{
	unsigned int workableWidth = framebuffer.width - 2 * length,
		workableHeigth = framebuffer.height - 2 * length;

	std::vector< std::tuple< unsigned int, unsigned int > > positions;

	positions.push_back(std::make_tuple(length + rand() % workableWidth, length + rand() % workableHeigth));

	while (positions.size() != amount) // fill in l random distinct positions
	{
		std::tuple< unsigned int, unsigned int > nextPixel = std::make_tuple(length + rand() % workableWidth, length + rand() % workableHeigth);

		// position doesn't exist in the vector
		if (std::find(positions.begin(), positions.end(), nextPixel) == positions.end())
			positions.push_back(nextPixel);
	}

	return positions;
}

void drawSquareStartingOnPixel(Image& framebuffer, unsigned int xi, unsigned int yi, unsigned int length, bool onlyEdges)
{
	Color c(rand() % 255, rand() % 255, rand() % 255);

	if (onlyEdges)
	{
		drawLine(framebuffer, xi, yi, xi + length, yi, c);
		drawLine(framebuffer, xi, yi + length, xi + length, yi + length, c);
		drawLine(framebuffer, xi, yi, xi, yi + length, c);
		drawLine(framebuffer, xi + length, yi, xi + length, yi + length, c);
	}

	else
		for (unsigned int i = 0; i < length; i++)
			for (unsigned int j = 0; j < length; j++)
				framebuffer.setPixel(xi + i, yi + j, c);
}

void drawSquaresOnImage(Image& framebuffer, unsigned int amount, unsigned int length, bool onlyEdges)
{
	std::vector< std::tuple< unsigned int, unsigned int > > positions = getDrawablePixels(framebuffer, amount, length);

	for (std::tuple< unsigned int, unsigned int > p : positions)
		drawSquareStartingOnPixel(framebuffer, std::get<0>(p), std::get<1>(p), rand() % length, onlyEdges);
}

void drawCircleCenteredOnPixel(Image& framebuffer, unsigned int x, unsigned int y, unsigned int radius, bool onlyEdges)
{
	Color c(rand() % 255, rand() % 255, rand() % 255);

	for (unsigned int n = onlyEdges ? radius : 1; n <= radius; n++)
		for (unsigned int i = 0; i < (unsigned int)ceil(PI * n * n); i++)
			framebuffer.setPixel((unsigned int)(x + n * cos(i)), (unsigned int)(y + n * sin(i)), c);
}

void drawCirclesOnImage(Image& framebuffer, unsigned int amount, unsigned int radius, bool onlyEdges)
{
	std::vector< std::tuple< unsigned int, unsigned int > > positions = getDrawablePixels(framebuffer, amount, (unsigned int)ceil(sqrt(8 * radius * radius) / 2.0));

	for (std::tuple< unsigned int, unsigned int > p : positions)
		drawCircleCenteredOnPixel(framebuffer, std::get<0>(p), std::get<1>(p), rand() % radius, onlyEdges);
}


void pattern1(Image& framebuffer, bool onlyEdges)
{
	Color c(rand() % 255, rand() % 255, rand() % 255);

	unsigned int low_left_x = ceil(framebuffer.width * 0.2),
		low_left_y = ceil(framebuffer.height * 0.2),
		low_right_x = ceil(framebuffer.width * 0.8),
		low_right_y = ceil(framebuffer.height * 0.2),

		top_left_x = ceil(framebuffer.width * 0.2),
		top_left_y = ceil(framebuffer.height * 0.8),
		top_right_x = ceil(framebuffer.width * 0.8),
		top_right_y = ceil(framebuffer.height * 0.8);

	drawLine(framebuffer, low_left_x, low_left_y, low_right_x, low_right_y, c);
	drawLine(framebuffer, low_left_x, low_left_y, top_left_x, top_left_y, c);
	drawLine(framebuffer, top_right_x, top_right_y, top_left_x, top_left_y, c);
	drawLine(framebuffer, top_right_x, top_right_y, low_right_x, low_right_y, c);

	drawCircleCenteredOnPixel(framebuffer, low_left_x, low_left_y, 50, onlyEdges);
	drawCircleCenteredOnPixel(framebuffer, low_right_x, low_right_y, 50, onlyEdges);
	drawCircleCenteredOnPixel(framebuffer, top_left_x, top_left_y, 50, onlyEdges);
	drawCircleCenteredOnPixel(framebuffer, top_right_x, top_right_y, 50, onlyEdges);

	drawCircleCenteredOnPixel(framebuffer, (unsigned int)ceil(framebuffer.width / 2.0), (unsigned int)ceil(framebuffer.height / 2.0), 160, true);

	drawLine(framebuffer,
		(unsigned int)ceil(framebuffer.width / 2.0),
		(unsigned int)ceil(framebuffer.height / 2.0),
		(unsigned int)ceil(framebuffer.width / 2.0 + 160 * cos(time(NULL))),
		(unsigned int)ceil(framebuffer.height / 2.0 + 160 * sin(time(NULL))), c);
}
int numberOfRandomFigures = 3;
bool onlyEdges = true;

Image framebuffer8(1080, 1920);
//render one frame
void Application::render(void)
{
	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	Image framebuffer( window_width, window_height );
	Image framebuffer2(800, 600);
	if (modo == 1){
		framebuffer2.fill(Color(0, 0, 0));
		dividePixel(&framebuffer);
		showImage(&framebuffer);
		prev_state = 1;
	}
	else if (modo == 2) {
		/*spiral(&framebuffer, 400, 300);
		drawForms(&framebuffer);
		showImage(&framebuffer);*/
		framebuffer2.fill(Color(0, 0, 0));
		setBackgroundColor(framebuffer2, Color::BLACK);
		drawCirclesOnImage(framebuffer2, numberOfRandomFigures, 150, onlyEdges);
		drawSquaresOnImage(framebuffer2, numberOfRandomFigures, 150, onlyEdges);
		showImage(&framebuffer2);
		Sleep(100);
		prev_state = 2;

	}
	else if (modo == 3) {
		framebuffer2.fill(Color(0, 0, 0));
		drawSnow(&framebuffer);
		showImage(&framebuffer);
		prev_state = 3;
	}
	else if (modo == 4) {
		framebuffer2.fill(Color(0, 0, 0));
		//drawImage(&framebuffer3);
		showImage(&framebuffer3);
		prev_state = 4;

	}
	else if (modo == 5) {
		circle(&framebuffer2, clicX, clicY);
		showImage(&framebuffer2);
		prev_state = 5;
	}
	else if (modo == 6) {
		if (prev_state != 6) {
			framebuffer4.loadTGA("bubbles.tga");
		}
		showImage(&framebuffer4);
		prev_state = 6;
	}
	else if (modo == 7) {
		setBackgroundColor(framebuffer7, Color::BLACK);
		pattern1(framebuffer7, onlyEdges);
		showImage(&framebuffer7);
		prev_state = 7;
	}
	else if (modo == 8) {
		showImage(&framebuffer8);
		prev_state = 8;
	}
	else{
		framebuffer2.fill(Color(0, 0, 0));
		bigerPixel(&framebuffer);
		showImage(&framebuffer);
	}

	//here you can add your code to fill the framebuffer

	//send image to screen
	
}

//called after render
void Application::update(double seconds_elapsed)
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	if (keystate[SDL_SCANCODE_SPACE]) //if key space is pressed
	{
		count = 0;
		changeRoute = 0;
		modo = 0;

	}
	if (keystate[SDL_SCANCODE_1]) //if key 1 is pressed
	{
		count = 0;
		changeRoute = 0;
		modo = 1;
	}
	if (keystate[SDL_SCANCODE_2]) //if key 2 is pressed
	{
		count = 0;
		modo = 2;
	}
	if (keystate[SDL_SCANCODE_3]) //if key 2 is pressed
	{
		count = 0;
		modo = 3;
	}
	if (keystate[SDL_SCANCODE_4]) //if key 2 is pressed
	{
		count = 0;
		modo = 4;
	}
	if (keystate[SDL_SCANCODE_6]) //if key 2 is pressed
	{
		count = 0;
		modo = 6;
		altereImage(framebuffer4);
	}
	if (keystate[SDL_SCANCODE_7]) //if key 2 is pressed
	{
		count = 0;
		modo = 7;
	}
	if (keystate[SDL_SCANCODE_8]) //if key 2 is pressed
	{
		count = 0;
		modo = 8;
	}
	if (keystate[SDL_SCANCODE_UP]) {
		numberOfRandomFigures++;
	}
	if (keystate[SDL_SCANCODE_DOWN]) {
		numberOfRandomFigures--;
	}
	if (keystate[SDL_SCANCODE_F]) {
		onlyEdges = false;
	}
	if (keystate[SDL_SCANCODE_U]) {
		onlyEdges = true;
	}
	

	//to read mouse position use mouse_position
}

//keyboard press event 
void Application::onKeyDown( SDL_KeyboardEvent event )
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	switch(event.keysym.scancode)
	{
		case SDL_SCANCODE_ESCAPE:
			exit(0); 
			break; //ESC key, kill the app
	}
}

//keyboard key up event 
void Application::onKeyUp(SDL_KeyboardEvent event)
{
	//...
}

//mouse button event
void Application::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (modo == 8) // draw circles and squares upon clicking only when in this mode
	{
		if (event.button == SDL_BUTTON_LEFT) //left mouse unpressed
		{
			drawCircleCenteredOnPixel(framebuffer8, mouse_position.x, mouse_position.y, rand() % 150, onlyEdges);
		}

		else if (event.button == SDL_BUTTON_RIGHT) //left mouse unpressed
		{
			drawSquareStartingOnPixel(framebuffer8, mouse_position.x, mouse_position.y, rand() % 150, onlyEdges);
		}
	}
	else if (event.button == SDL_BUTTON_LEFT) //LEFT mouse pressed
	{
		if (modo == 4) {
			drawImage(&framebuffer3);
		}
		else if (modo == 3) {
			if (size < 0) {
				size = 0;
			}
			else {
				size = size - 100;
			}
			if (size == 0) {
				size = size + 1000;
			}
		}
		else {
			clicX = mouse_position.x;
			clicY = mouse_position.y;
			count = 0;
			modo = 5;
		}
	}
}

// Draw geometric figures: circles with left click and squares with right clicks
void Application::onMouseButtonUp( SDL_MouseButtonEvent event )
{
}

//when the app starts
void Application::start()
{
	for (int i = 0; i < size; i++) {
		arrayX[i] = (rand() % 800);
	}
	for (int i = 0; i < size; i++) {
		arrayY[i] = (rand() % 600);
	}
	for (int i = 0; i < size; i++) {
		randoms[i] = rand();
	}
	framebuffer3.loadTGA("starnight.tga");
	framebuffer3.flipY();
	std::cout << "launching loop..." << std::endl;
	launchLoop(this);
}
