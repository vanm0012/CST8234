/* PROGRAM:  particle header
   AUTHOR:   Tryton Van Meer
   DATE:     November 2015
   PURPOSE:  Assignment 2
*/

#ifndef VANMEER_PARTICLE_H
#define VANMEER_PARTICLE_H


/**************************************************************************/
/* Macro Defines
**************************************************************************/
#define DFLT_INIT_NUM_PARTICLES 50
#define DELTA_LIFE_SPAN 1


/**************************************************************************/
/* Declare Structures
**************************************************************************/
struct colour
{
  float r;
  float g;
  float b;
  float a;
};
typedef struct colour Colour4;

struct vector
{
  float x;
  float y;
  float z;
};
typedef struct vector Point3D;
typedef struct vector Vector3D;

struct particle
{
  Colour4           col;
  Point3D           pos;
  Vector3D          dir;
  Vector3D          spd;
  int               lifespan;
  int               size;
  struct particle*  next;
};


/**************************************************************************/
/* Function prototypes
**************************************************************************/
int particle_init( struct particle* p );
int particle_add( struct particle **head );
int particle_remove( struct particle* p );
int particle_destroy( struct particle **head );
int particle_update( struct particle **head );

int get_random_int(int r);


#endif /* VANMEER_PARTICLE_H */
