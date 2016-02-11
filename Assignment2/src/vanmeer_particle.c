/* PROGRAM:  particle
   AUTHOR:   Tryton Van Meer
   DATE:     November 2015
   PURPOSE:  Assignment 2
*/

/**************************************************************************/
/* Declare include files
**************************************************************************/
#include "vanmeer_particle.h"
#include <stdlib.h>
#include <time.h>


/*******************************************************************************
 * FUNCTION : particle_init
 * PURPOSE  : initialize the properties of a single particle
 * INPUT    : pointer to the particle structure to be initialized
 * OUTPUT   : returns -1 on error, 0 on success
 * NOTES    :
 *******************************************************************************/
int particle_init( struct particle* p )
{
  int direction = get_random_int(8);

  /* set the particles properties */
  p->col.r = 0;
  p->col.g = 0;
  p->col.b = 0;
  p->col.a = 1.0;

  p->pos.x = 0;
  p->pos.y = 0;

  p->spd.x = 0.1 * (get_random_int(8) + 1);
  p->spd.y = 0.1 * (get_random_int(8) + 1);


  switch (direction)
  {
    case 0:
      p->dir.x = 0.5;
      p->dir.y = 0;
      break;
    case 1:
      p->dir.x = -0.5;
      p->dir.y = 0;
      break;
    case 2:
      p->dir.x = 0;
      p->dir.y = 0.5;
      break;
    case 3:
      p->dir.x = 0;
      p->dir.y = -0.5;
      break;
    case 4:
      p->dir.x = 0.5;
      p->dir.y = -0.5;
      break;
    case 5:
      p->dir.x = -0.5;
      p->dir.y = 0.5;
      break;
    case 6:
      p->dir.x = 0.5;
      p->dir.y = 0.5;
      break;
    case 7:
      p->dir.x = -0.5;
      p->dir.y = -0.5;
      break;
  }

  p->lifespan = get_random_int(100) + 100;
  p->size = 10;


  return 0;
}


/*******************************************************************************
 * FUNCTION : part#include <random>icle_add
 * PURPOSE  : add a particle to the dynamic particle linked list
 * INPUT    : struct particle *head. Head of the particle list
 * OUTPUT   : returns -1 on error, 0 on success
 * NOTES    : Calls particle_init()
 *******************************************************************************/
int particle_add( struct particle **head )
{
  struct particle *new_particle = (struct particle*)malloc(sizeof(struct particle));
  particle_init(new_particle);

  new_particle->next = *head;

  *head = new_particle;

  return 0;
}


/*******************************************************************************
 * FUNCTION : particle_remove
 * PURPOSE  : remove a specific particle from the dynamic particle linked list
 * INPUT    : pointer to the particle to remove
 * OUTPUT   : returns -1 on error, 0 on success
 * NOTES    : Particle can be situated in any place in the list.
 *            Usually deleted becuase the lifespan ran out
 *******************************************************************************/
int particle_remove( struct particle *p )
{
  struct particle *tmp = p->next;
  if(tmp == NULL)
  {
    p = NULL;
  }
    else
  {
    p->col = tmp->col;
    p->pos = tmp->pos;
    p->spd = tmp->spd;
    p->dir = tmp->dir;
    p->lifespan = tmp->lifespan;
    p->size = tmp->size;

    p->next = tmp->next;
  }

    free(tmp);
    tmp = NULL;

  return 0;
}


/********************************particle_update***********************************************
 * FUNCTION : particle_destroy
 * PURPOSE  : free memory used by the dynamic particle linked list
 * INPUT    : struct particle **head. Head of the particle list
 * OUTPUT   : returns -1 on error, the number of particles destroyed on success
 * NOTES    : removes all particles from the list
 *            Calls particle_remove
 *******************************************************************************/
int particle_destroy( struct particle **head )
{
  struct particle *temp = *head;
  int num_particles = 0;

  while(temp != NULL)
  {
    free(temp);
    temp = temp->next;
    num_particles++;
  }

  return num_particles;
}


/*******************************************************************************
 * FUNCTION : particle_update
 * PURPOSE  : update the particles properties to be rendered in the next frame
 * INPUT    : struct particle **head. Head of the particle list
 * OUTPUT   : returns -1 on error, 0 on success
 * NOTES    :
 *******************************************************************************/
int particle_update( struct particle **head )
{
  struct particle *temp = *head;

  while(temp != NULL)
  {
    temp->col.r = get_random_int(2);
    temp->col.g = get_random_int(2);
    temp->col.b = get_random_int(2);


    temp->pos.x += (temp->dir.x * temp->spd.x);
    temp->pos.y += (temp->dir.y * temp->spd.y);

    temp->lifespan -= DELTA_LIFE_SPAN;
    if (temp->lifespan < 0)
    {
      temp->col.a = 0;
      particle_remove(temp);
    }

    temp = temp->next;
  }

  return 0;
}


/*******************************************************************************
 * FUNCTION : get_random_int
 * PURPOSE  : Returns a random integer in a given range
 * INPUT    : Range of randomness
 * OUTPUT   : Integer chosen pseudorandomly
 * NOTES    :
 *******************************************************************************/
 int get_random_int(int r)
 {
   return rand() % r;
 }
