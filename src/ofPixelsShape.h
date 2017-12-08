#include "ofMain.h"

/*

	Author: Dario Longobardi 2017
	Drawing simple pixels shape

	draw:
	line, point, circle, rectangle, triangle, text

	utility:
	aspect ratio
	create font

	https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
	https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

*/

struct ofLetter
{
        char letter;
	ofImage img;
} _letter_;

struct ofRatio 
{
	int w;
	int h;
	float ratio;
} _ratio_ ;

class ofPixelsShape : public ofPixels
{
	public:
	const int WIDTH_LETTER;
	vector<ofLetter> LETTER;
	ofPixelsShape(): WIDTH_LETTER(32) { }

	int draw_char(ofPixels &_img, char c, ofPoint xy, int size = -1, ofColor color = ofColor::white)
	{
		c = toupper(c);
		for(unsigned int i = 0; i < LETTER.size(); i++) 
		{
			if(LETTER[i].letter == c) 
			{
				ofPixels let = LETTER[i].img.getPixels();
				if( size > 0 ) 
				{
					let.resize( size, size );
				}
		                let.setImageType(OF_IMAGE_COLOR);
				let.blendInto( _img, (int)xy.x, (int)xy.y );
			}
                }
		return 1;
	}

	int draw_string(ofPixels &_img, string str, ofPoint xy, int size = -1, ofColor color = ofColor::white) 
	{
	    	for (unsigned int i = 0; i < str.length(); i++) {
        		draw_char(_img, str[i], xy, size, color);
		        xy.x += (size>0)?size:WIDTH_LETTER;
		}
		return 1;
	}

	int draw_point(ofPixels &_img, ofPoint xy0, ofColor color = ofColor::white)
	{
		if(xy0.x<0||xy0.x>_img.getWidth()||xy0.y<0||xy0.y>_img.getHeight()) return -1;
		_img.setColor(xy0.x,xy0.y,color);
		return 1;
	}

	int draw_line(ofPixels &_img, ofPoint xy0, ofPoint xy1, ofColor color = ofColor::white) 
	{
		int _w = _img.getWidth();
		int _h = _img.getHeight();
		if(xy0.x<0||xy0.x>_w||xy0.y<0||xy0.y>_h||xy1.x<0||xy1.x>_w||xy1.y<0||xy1.y>_h) return -1;

		int dx = abs(xy1.x-xy0.x), sx = xy0.x<xy1.x ? 1 : -1;
		int dy = abs(xy1.y-xy0.y), sy = xy0.y<xy1.y ? 1 : -1; 
		int err = (dx>dy ? dx : -dy)/2, e2;
 		for(;;){
		    _img.setColor(xy0.x,xy0.y,color);
		    if (xy0.x==xy1.x && xy0.y==xy1.y) break;
		    e2 = err;
		    if (e2 >-dx) { err -= dy; xy0.x += sx; }
		    if (e2 < dy) { err += dx; xy0.y += sy; }
		}
		return 1;
	}

	int draw_triangle(ofPixels &_img, ofPoint xy0, ofPoint xy1, ofPoint xy2, ofColor color = ofColor::white, bool fill=true)
	{
		int _w = _img.getWidth();
		int _h = _img.getHeight();
		if(xy0.x<0||xy0.x>_w||xy0.y<0||xy0.y>_h||xy1.x<0||xy1.x>_w||xy1.y<0||xy1.y>_h||xy2.x<0||xy2.x>_w||xy2.y<0||xy2.y>_h) return -1;

		draw_line(_img, xy0, xy1, color);
		draw_line(_img, xy2, xy1, color);
		draw_line(_img, xy2, xy0, color);

		if(fill) {
			//not work
		}
		return 1;
	}

	int draw_circle(ofPixels &_img, ofPoint xy, int radius, ofColor color = ofColor::white, bool fill=true)
	{
		int x = radius-1;
	    	int y = 0;
		int dx = 1;
	    	int dy = 1;
	    	int err = dx - (radius << 1);
		int _w = _img.getWidth();
		int _h = _img.getHeight();

		if(xy.x<0||xy.y<0||xy.x+radius>_w||xy.y+radius>_h) return -1;

		while (x >= y)
		{
			_img.setColor(xy.x + x, xy.y + y, color);
			_img.setColor(xy.x + y, xy.y + x, color);
			_img.setColor(xy.x - y, xy.y + x, color);
			_img.setColor(xy.x - x, xy.y + y, color);
			_img.setColor(xy.x - x, xy.y - y, color);
			_img.setColor(xy.x - y, xy.y - x, color);
			_img.setColor(xy.x + y, xy.y - x, color);
			_img.setColor(xy.x + x, xy.y - y, color);

			if (err <= 0)
			{
				y++;
				err += dy;
				dy += 2;
			}
			if (err > 0)
			{
				x--;
				dx += 2;
				err += dx - (radius << 1);
			}
		}

		if(fill)
		for(int yu=-radius; yu<=radius; yu++)
		    for(int xu=-radius; xu<=radius; xu++)
		        if(xu*xu+yu*yu <= radius*radius)
		            _img.setColor(xy.x+xu, xy.y+yu, color);

	    	return 1;
	}

	int draw_rectangle(ofPixels &_img, ofRectangle rect, ofColor color = ofColor::white, bool fill=true)
	{
		int _w = _img.getWidth();
		int _h = _img.getHeight();
		int xs = rect.x;
		int ys = rect.y;
		int width  = rect.width  + xs;
		int height = rect.height + ys;
		if(xs<0||xs>_w||ys<0||ys>_h||width>_w||height>_h) return -1;
		if(!fill)
		{
			for(int y = ys; y < height; y++) _img.setColor(xs,y,color); 
			for(int x = xs; x < width; x++)  _img.setColor(x,ys,color); 
			for(int y = ys; y < height; y++) _img.setColor(width,y,color); 
			for(int x = xs; x < width; x++)  _img.setColor(x,height,color); 
		}
		else{
			for(int y = ys; y < height; y++) {
				for(int x = xs; x < width; x++) {
					_img.setColor(x,y,color); 
				}
			}
		}
		return 1;
	}

	ofRatio aspect_ratio(ofPixels img, unsigned int maxWidth, unsigned int maxHeight)
        {
                if (img.getWidth() > maxWidth || img.getHeight() > maxHeight)
                {
                        double widthRatio = (double) img.getWidth() / (double) maxWidth;
                        double heightRatio = (double) img.getHeight() / (double) maxHeight;
                        double ratio = max(widthRatio, heightRatio);
                        int newWidth = (int) (img.getWidth() / ratio);
                        int newHeight = (int) (img.getHeight() / ratio);
			_ratio_.w     = newWidth;
			_ratio_.h     = newHeight;
			_ratio_.ratio = ratio;
                        return _ratio_;
                }
        }

	void create_font(string path)
        {
                vector<char> list_letter;
                vector<ofImage> list_img;
                ofDirectory dir(path);
                dir.allowExt("png");
                dir.listDir();
                dir.sort(); 
                for(unsigned int i = 0; i < dir.size(); i++) {
                        string name = dir.getName(i);
                        ofStringReplace(name,".png","");
                        char n = name[0];
                        ofImage im;
                        im.load(dir.getPath(i));
                        list_letter.push_back(n);
                        list_img.push_back(im);
                        cout << n << " ";
                }
                cout << endl << endl;
                if(list_img.size()==list_letter.size()) {
			for(unsigned int i = 0; i < list_img.size(); i++)
			{
				ofLetter l;
				l.letter = list_letter[i];
				l.img    = list_img[i];
				LETTER.push_back(l);
			}
		}
        }
};
