#include "precompiled.h"

void Mouse( int button, int state, int x, int y)
{
  x /= 10.0f;
  y /= 10.0f;
  
  if (state == GLUT_DOWN)
    switch(button)
    {
      case GLUT_LEFT_BUTTON:
        {
          uint32 count = (uint32)random( 3 );
          real e = Random( 5, 10);
          
          for(uint32 i = 0; i < count; ++i)
            vertices[i].set Random;
          poly.set (vertices, count);
        }
        break;
      case GLUT_RIGHT_BUTTON:
        {
          Circle c(random(1.0f, 3.0f));
          body *b = scene.Add(&c, x, y);
        }
        break;
    }
}

void Keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
    case ESC_KEY:
      exit(0);
      break;
    case 's':
      {
        
      }
      break;
    case 'd':
      {
        
      }
      break;
    case 'f':
      break;
    case ' ':
      canStep = true;
      break;
      
  }
}

int main(int argc, char** argv)
{
   glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow( "PhyEngine" );
    glutDisplayFunc( PhysicsLoop );
    glutKeyboardFunc( Keyboard );
    glutMouseFunc( Mouse );
    glutIdleFunc( PhysicsLoop );

    glMatrixMode( GL_PROJECTION );
    glPushMatrix( );
    glLoadIdentity( );
    gluOrtho2D( 0, 80, 60, 0 );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );
    glLoadIdentity( );
  
  return 0;
}
