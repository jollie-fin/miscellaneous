#include <cstdlib>
#include <cstdio>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

int ***coloriage;
int taille;

void set_couleur(int couleur, int nb_couleur)
{
  long angle = 256.*6.*double(couleur)/double(nb_couleur);
  if (angle < 256)
    glColor3ub(255,0,255-(angle));
  else if (angle < 2*256)
    glColor3ub(255,angle-256,0);
  else if (angle < 3*256)
    glColor3ub(255-(angle-2*256),255,0);
  else if (angle < 4*256)
    glColor3ub(0,255,(angle-3*256));
  else if (angle < 5*256)
    glColor3ub(0,255-(angle-4*256),255);
  else if (angle < 6*256)
    glColor3ub(angle-5*256,0,255);
  else
    exit(0);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Mon premier programme OpenGL !",NULL);
    SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

    bool continuer = true;
    SDL_Event event;

    int couleur = 0;
    int nb_couleur = 10;
    bool continuer = true;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = false;
                break;
            case SDL_KEYDOWN:
              switch (event.key.keysym.sym)
              {
                  case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                    continuer = false;
                    break;
                  case SDLK_UP:
                    couleur++;
                    if (couleur >= nb_couleur)
                      couleur = 0;
                    break;
                  case SDLK_DOWN:
                    couleur--;
                    if (couleur <0)
                      couleur = nb_couleur-1;
                    break;
                  default:
                    break;
              }
              break;
            default:
              break;
             
        }

        glClear(GL_COLOR_BUFFER_BIT);

        set_couleur(couleur, nb_couleur);

        glBegin(GL_QUADS);
        
        for (int x = 0; x < taille; x++)
          for (int y = 0; y < taille; y++)
            for (int z = 0; z < taille; z++)
              {
                if ((z!=0)&&(coloriage[x][y][z]!=coloriage[x][y][z-1])&&(coloriage[x][y][z]==couleur))
                {
                  glNormal3i(0,0,1);
                  glVertex3i(x,y,z);
                  glVertex3i(x+1,y,z);
                  glVertex3i(x+1,y+1,z);
                  glVertex3i(x,y+1,z);

                  glNormal3i(0,0,-1);
                  glVertex3i(x,y,z);
                  glVertex3i(x+1,y,z);
                  glVertex3i(x+1,y+1,z);
                  glVertex3i(x,y+1,z);
                }
                if ((z!=taille-1)&&(coloriage[x][y][z]!=coloriage[x][y][z+1])&&(coloriage[x][y][z]==couleur))
                {
                  glNormal3i(0,0,1);
                  glVertex3i(x,y,z+1);
                  glVertex3i(x+1,y,z+1);
                  glVertex3i(x+1,y+1,z+1);
                  glVertex3i(x,y+1,z+1);

                  glNormal3i(0,0,-1);
                  glVertex3i(x,y,z+1);
                  glVertex3i(x+1,y,z+1);
                  glVertex3i(x+1,y+1,z+1);
                  glVertex3i(x,y+1,z+1);
                }


                if ((y!=0)&&(coloriage[x][y][z]!=coloriage[x][y-1][z])&&(coloriage[x][y][z]==couleur))
                {
                  glNormal3i(0,1,0);
                  glVertex3i(x,y,z);
                  glVertex3i(x+1,y,z);
                  glVertex3i(x+1,y,z+1);
                  glVertex3i(x,y,z+1);

                  glNormal3i(0,-1,0);
                  glVertex3i(x,y,z);
                  glVertex3i(x+1,y,z);
                  glVertex3i(x+1,y,z+1);
                  glVertex3i(x,y,z+1);
                }
                if ((y!=taille-1)&&(coloriage[x][y][z]!=coloriage[x][y+1][z])&&(coloriage[x][y][z]==couleur))
                {
                  glNormal3i(0,1,0);
                  glVertex3i(x,y+1,z);
                  glVertex3i(x+1,y+1,z);
                  glVertex3i(x+1,y+1,z+1);
                  glVertex3i(x,y+1,z+1);

                  glNormal3i(0,-1,0);
                  glVertex3i(x,y+1,z);
                  glVertex3i(x+1,y+1,z);
                  glVertex3i(x+1,y+1,z+1);
                  glVertex3i(x,y+1,z+1);
                }


                if ((x!=0)&&(coloriage[x][y][z]!=coloriage[x-1][y][z])&&(coloriage[x][y][z]==couleur))
                {
                  glNormal3i(1,0,0);
                  glVertex3i(x,y,z);
                  glVertex3i(x,y+1,z);
                  glVertex3i(x,y+1,z+1);
                  glVertex3i(x,y,z+1);

                  glNormal3i(-1,0,0);
                  glVertex3i(x,y,z);
                  glVertex3i(x,y+1,z);
                  glVertex3i(x,y+1,z+1);
                  glVertex3i(x,y,z+1);
                }
                if ((x!=taille-1)&&(coloriage[x][y][z]!=coloriage[x+1][y][z])&&(coloriage[x][y][z]==couleur))
                {
                  glNormal3i(1,0,0);
                  glVertex3i(x+1,y,z);
                  glVertex3i(x+1,y+1,z);
                  glVertex3i(x+1,y+1,z+1);
                  glVertex3i(x+1,y,z+1);

                  glNormal3i(-1,0,0);
                  glVertex3i(x+1,y,z);
                  glVertex3i(x+1,y+1,z);
                  glVertex3i(x+1,y+1,z+1);
                  glVertex3i(x+1,y,z+1);
                }
              }
 
        glEnd();

        glFlush();
        SDL_GL_SwapBuffers();
    }

    SDL_Quit();

    return 0;
}
