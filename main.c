#include <allegro.h>
void movBol();
void control();
int colidir(int px, int py, int pw, int ph, int bx, int by, int bw, int bh);

class Player{
	public:
		Player(int x,int y,int w int h){
			this->x=x;
			this->y=y;
			this->w=w;
			this->h=h;
		}
		void setX(int value){
			this->x=value;
		}
		void setY(int value){
            this->y=value;
        }
		void setW(int value){
            this->w=value;
        }
		void setH(int value){
            this->h=value;
        }
        int getX(){
            return this->x;
        }
		int getY(){
            return this->y;
        }
		int getW(){
            return this->w;
        }
		int getH(){
            return this->h;
        }
	private:
		int x;
		int y;
		int w;
		int h;
};

struct obj{ int x, y, w, h;};
struct obj
	 p1 = {10,350,10,50}, 
	 p2 = {870,350,10,50},
	 b1 = {200,300, 8, 8}
;

int vx     = 5;
int vy     = 5;
int width  = 900;
int height = 700;

BITMAP *buffer, *itens;

int main() {
	allegro_init();
    install_keyboard();
	set_color_depth(32);
	set_window_title("Pong");
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
	buffer = create_bitmap(width, height);
	itens  = load_bitmap("img/itens.bmp", NULL);
		
	while (!(key[KEY_ESC])){	
		movBol();
		control();		
		masked_blit(itens, buffer, 0, 0, p1.x, p1.y, p1.w, p1.h);
		masked_blit(itens, buffer, 0, 0, p2.x, p2.y, p2.w, p2.h);
		masked_blit(itens, buffer, 0, 0, b1.x, b1.y, b1.w, b1.h);
		draw_sprite(screen, buffer, 0, 0);
		rest(10);
		clear(buffer);		
	}
	destroy_bitmap(buffer);
	destroy_bitmap(itens);
	return 0;
}
END_OF_MAIN();

void control(){
	if(key[KEY_DOWN]  && p1.y < height-40) p1.y+= 10;
	else if(key[KEY_UP]    && p1.y > 0  ) p1.y-= 10;
	if(b1.x > width/2){
		if(b1.y > p2.y) p2.y += 10;	
		if(b1.y < p2.y) p2.y -= 10;
	}		
}

void movBol(){
	b1.x += vx;
	b1.y += vy;	
	if(b1.x <=   0 || b1.x >= width) {
		b1.x=300;
		vx=-vx;
	}
	if(b1.y <= 0 || b1.y > height-10) vy = -vy;
	if(colidir(b1.x, b1.y, p1.x, p1.y, b1.w, b1.h, p1.w, p1.h)) vx = 5;
	if(colidir(b1.x, b1.y, p2.x, p2.y, b1.w, b1.h, p2.w, p2.h)) vx =-5;
}

int colidir(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh){		
	if(Ax + Aw > Bx && Ax < Bx + Bw && Ay + Ah > By && Ay < By + Bh) 
	return 1; 
	return 0;	
}
