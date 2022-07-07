#include <allegro.h>
int width  = 900;
int height = 700;
int vx = 5;
int vy = 5;
void movBol();
void control();
int colidir(int px, int py, int pw, int ph, int bx, int by, int bw, int bh);
class Objeto{
	public:
		Objeto(int x,int y,int w,int h){
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
class Bola : public Objeto{
    public:
		Bola(int x,int y,int w,int h):Objeto(x,y,w,h){}
        void movBol(int p1x,int p1y, int p1h,int p1w,int p2x,int p2y, int p2h,int p2w){
	            this->setX((this->getX()+vx));
                this->setY((this->getY()+vy));
                if(this->getX() <=   0 || this->getX() >= width) {
                    this->setX(300);
                    vx=-vx;
                }
                if(this->getY() <= 0 || this->getY() > height-10) vy = -vy;
                if(this->colidir(p1x, p1y, p1w, p1h)) vx = 5;
                if(this->colidir(p2x, p2y, p2w, p2h)) vx =-5;
        }
    private:
        int colidir(int Ax, int Ay, int Aw, int Ah){		
            if(Ax + Aw > this->getX() && Ax < this->getX() + this->getW() && Ay + Ah > this->getY() && Ay < this->getY() + this->getH())
                return 1; 
            return 0;	
        }
};
class Player : public Objeto{
	public:
		Player(int x,int y,int w,int h):Objeto(x,y,w,h){}
		void control(){
			if(key[KEY_DOWN]  && this->getY() < height-50) this->setY((this->getY()+10));
			else if(key[KEY_UP]    && this->getY() > 0  ) this->setY((this->getY()-10));
		}
};
class Bot : public Objeto{
	public:
		Bot(int x,int y,int w,int h):Objeto(x,y,w,h){}	
		void control(int b1x,int b1y){
			if(b1x > width/2){
				if(b1y > this->getY() && this->getY() < height-50) this->setY((this->getY()+10));	
				if(b1y < this->getY() && this->getY() > 0) this->setY((this->getY()-10));
			}
		}
};
Player p1(25,350,10,50);
Bot p2(865,350,10,50);
Bola b1(200,300,8,8);
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
		b1.movBol(p1.getX(),p1.getY(),p1.getH(),p1.getW(),p2.getX(),p2.getY(),p2.getH(),p2.getW());
		p1.control();
		p2.control(b1.getX(),b1.getY());
		masked_blit(itens, buffer, 0, 0, p1.getX(), p1.getY(), p1.getW(), p1.getH());
		masked_blit(itens, buffer, 0, 0, p2.getX(), p2.getY(), p2.getW(), p2.getH());
		masked_blit(itens, buffer, 0, 0, b1.getX(), b1.getY(), b1.getW(), b1.getH());
		draw_sprite(screen, buffer, 0, 0);
		rest(10);
		clear(buffer);		
	}
	destroy_bitmap(buffer);
	destroy_bitmap(itens);
	return 0;
}
END_OF_MAIN();
