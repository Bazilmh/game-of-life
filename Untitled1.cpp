#include <windows.h>
#include <iostream>
#include <SDL.h>
#include <math.h>

#define NUM_MIN 0.0000000000000000001

Uint32 color=0x000000;
Uint32 * pixels = new Uint32[640 * 480];
bool * buffer = new bool[640 * 480];
bool * temp = new bool[640*480];


int MOUSE_X,MOUSE_Y;

int GAME_STATE = 0;

using namespace std;

char ch;


//------------------------------------------------------------------------------
void putpixel(int x,int y,int resx,int resy,Uint32 col)
{

 pixels[resx*y+x] = col;

}

//------------------------------------------------------------------------------
Uint32 getpixel(int x,int y,int resx,int resy)
{
return (buffer[resx*y+x]);     
}


//------------------------------------------------------------------------------
void putpixels(int x,int y,int resx,int resy,int len,Uint32 col)
{
len = x+len;
 for(int i=x;i<len;i++)
 pixels[resx*y+i] = col;

}


//------------------------------------------------------------------------------
int random(int a,int b,int d)  //argument d is provided as relaxation time for getting random values in a loop. Generally d >= 700000 for loop.
{                              //for generating random number out of a loop argument d can be zero.
int c = b-a;

for(int i=0;i<d;i++)
continue;       
       
return ((timeGetTime()%c)+a);   

}


void glider(int x,int y)
{

for(int i=0;i<3;i++)
buffer[(640*y)+(x+i)] = 1;

buffer[(640*(y+2))+(x+1)] = 1;
buffer[(640*(y+1))+(x+2)] = 1;

     
}

void glider_r(int x,int y)
{

for(int i=0;i<3;i++)
buffer[(640*y)+(x+i)] = 1;

buffer[(640*(y-2))+(x+1)] = 1;
buffer[(640*(y-1))+(x+2)] = 1;

     
}




void game_logic()
{

for(int i=0;i<(640*480);i++)
{temp[i] = 0;}



for(int i=1;i<640;i++)
{

for(int j=1;j<480;j++)
{

int count = 0;

temp[(640*j)+i] = buffer[(640*j)+i];

if(buffer[(640*j)+(i-1)] == 1)
{count++;}

if(buffer[(640*j)+(i+1)] == 1)
{count++;}

if(buffer[(640*(j+1))+(i-1)] == 1)
{count++;}

if(buffer[(640*(j+1))+(i)] == 1)
{count++;}

if(buffer[(640*(j+1))+(i+1)] == 1)
{count++;}

if(buffer[(640*(j-1))+(i-1)] == 1)
{count++;}

if(buffer[(640*(j-1))+(i)] == 1)
{count++;}

if(buffer[(640*(j-1))+(i+1)] == 1)
{count++;}

//if(count > 0)
//{cout<<"count :"<<count<<" || ";}


if(count == 3)
{
temp[(640*j)+i] = 1;

//cout<<"construction at "<<i<<","<<j<<" || ";
}
else
if(count <=1 || count >=4)
{
temp[(640*j)+i] = 0;

//cout<<"destruction at "<<i<<","<<j<<endl;
//system("pause");
}


        
}        
        
}

cout<<endl;
for(int i=0;i<(640*480);i++)
{

buffer[i] = temp[i];
        
}

/*
for(int i=0;i<50;i++)
{

for(int j=0;j<50;j++)
{

cout<<buffer[i];        
        
}

cout<<endl;

        
}
*/





//cout<<"\nloop complete \n";
//system("pause");
     
}

void display()
{
for(int i=0;i<640;i++)
{

for(int j=0;j<480;j++)
{

if(buffer[(640*j)+i] == 1)
{pixels[(640*j)+i] = 0x00ff00;}

        
}        
        
}

     
     
}




//------------------------------------------------------------------------------
void setup()
{

}

void render()
{
     
//code here
display();

if(GAME_STATE == 1)
game_logic();



}

int main(int argc, char ** argv)
{
    bool leftMouseButtonDown = false;
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("Game of life - Press s to start and q to pause.",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);
    

    
     
    //memset(pixels, 125, 640 * 480 * sizeof(Uint32));
    
     
    setup(); 
    
    while (!quit)
    {
        SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));

      
         while( SDL_PollEvent( &event ) != 0 )
                {
                    //User requests quit
                    if( event.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    
                    if(event.type == SDL_KEYDOWN)
                    {
           
                      //cout<<char(event.key.keysym.sym)<<endl;  
                      
                      if(char(event.key.keysym.sym) == 's')
                      GAME_STATE = 1;
                      else
                      if(char(event.key.keysym.sym) == 'p')
                      GAME_STATE = 0;
                      else
                      if(char(event.key.keysym.sym) == 'g')
                      {
                      SDL_GetMouseState(&MOUSE_X,&MOUSE_Y);
                      glider(MOUSE_X,MOUSE_Y);
                      }
                      else
                      if(char(event.key.keysym.sym) == 'r')
                      {
                      SDL_GetMouseState(&MOUSE_X,&MOUSE_Y);
                      glider_r(MOUSE_X,MOUSE_Y);
                      }
                      else
                      if(char(event.key.keysym.sym) == 'c')
                      {
                      
                      for(int i=0;i<(640*480);i++)
                      {buffer[i] = 0;}                              
                     
                      
                      }
                      
                      
                               
                    }
                     
                    if(event.type==SDL_MOUSEBUTTONDOWN)
                    {
                                                       
                     //cout<<"clicked"<<endl; 
                     SDL_GetMouseState(&MOUSE_X,&MOUSE_Y);
                     buffer[MOUSE_Y*640+MOUSE_X] = 1;                                  
                                                        
                    }  
 
                    
                    
                }
 
                    memset(pixels, 0, 640 * 480 * sizeof(Uint32));
            
                    render();
               

                
              
 
                    
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    delete[] pixels;
    delete[] buffer;
    delete[] temp;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
