#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct particle
{
  double pos_x;
  double pos_y;
  double mass;
  double vel_x;
  double vel_y;
  double brightness;
} particle_t;

int getInput(char* filename, particle_t* data, int N);
int setOutput(char* filename, particle_t* data, int N);
void calculateNewPositions(particle_t* data, int N, int nsteps, double dt);

void print_array(particle_t* particles, int N);

int main(int argc, char* argv[])
{
  if (argc != 6)
  {
    printf("Check your input..\n");
    return -1;
  }

  int N, nsteps, graphics;
  double dt;
  particle_t* data = (particle_t*)malloc(N*sizeof(particle_t));

  N = atoi(argv[1]);
  char* filename = argv[2];
  nsteps = atoi(argv[3]);
  dt = atof(argv[4]);
  graphics = atoi(argv[5]);
  char* filename_out = "result.gal";

  int err = getInput(filename, data, N);
  if(err == -1)
  {
    return -1;
  }
  calculateNewPositions(data, N, nsteps, dt);

  err = setOutput(filename_out, data, N);
  if(err == -1)
  {
    return -1;
  }

  free(data);
  return 0;
}

int getInput(char* filename, particle_t* data, int N)
{
  FILE *stream_in;
  stream_in = fopen(filename,"rb");
  double* arr = (double*)malloc(N*6*sizeof(double));

  if(stream_in == NULL)
  {
    printf("Error: unable to open file: %s\n", filename);
    return -1;
  }
  size_t input_size = N*6*sizeof(double);

  /* Read input to data array */
  size_t items_read = fread(arr, sizeof(char), input_size, stream_in);
  int j = 0;
  for (int i = 0; i < N*6; i += 6)
  {
    data[j].pos_x = arr[i];
    data[j].pos_y = arr[i+1];
    data[j].mass = arr[i+2];
    data[j].vel_x = arr[i+3];
    data[j].vel_y = arr[i+4];
    data[j].brightness = arr[i+5];
    j++;
  }

  if (items_read != input_size)
  {
    printf("Error reading the input file.\n");
    return -1;
  }

  fclose(stream_in);
  return 1;
}

int setOutput(char* filename, particle_t* data, int N)
{
  FILE *stream_out;
  stream_out = fopen(filename,"wb");
  if(stream_in == NULL)
  {
    printf("Error: unable to open file: %s\n", filename);
    return -1;
  }
  fwrite(data, sizeof(particle_t), N, stream_out);
  fclose(stream_out);
  return 0;
}

void calculateNewPositions(particle_t* particles, int N, int nsteps, double dt)
{
  double Fx, Fy, ax, ay, r;
  double G = 100/(double)(N);
  double epsilon = 0.001;
  particle_t *particles_new = (particle_t*)malloc(N*sizeof(particle_t));
  *particles_new = *particles;
  for (int n = 0; n < nsteps; n++)
  {
    for(int i = 0; i < N; i++)
    {
      Fx = 0;
      Fy = 0;
      for(int j = 0; j < N; j++)
      {
        if (j != i)
        {
          r = sqrt((particles[i].pos_x - particles[j].pos_x)*(particles[i].pos_x - particles[j].pos_x) + (particles[i].pos_y - particles[j].pos_y)*(particles[i].pos_y - particles[j].pos_y));
          Fx += particles[j].mass*(particles[i].pos_x - particles[j].pos_x)/pow((r+epsilon),3);
          Fy += particles[j].mass*(particles[i].pos_y - particles[j].pos_y)/pow((r+epsilon),3);
        }
      }
      /* Forces */
      Fx *= -G*particles[i].mass;
      Fy *= -G*particles[i].mass;
      /* Acceleration */
      ax = Fx/(particles[i].mass);
      ay = Fy/(particles[i].mass);
      /* Updating velocities */
      particles_new[i].vel_x = particles[i].vel_x + dt*ax;
      particles_new[i].vel_y = particles[i].vel_y + dt*ay;
      /* Updating positions */
      particles_new[i].pos_x = particles[i].pos_x + dt* particles_new[i].vel_x;
      particles_new[i].pos_y = particles[i].pos_y + dt* particles_new[i].vel_y;
    }
    for (int i = 0; i < N; i++)
    {
      particles[i].pos_x = particles_new[i].pos_x;
      particles[i].pos_y = particles_new[i].pos_y;
      particles[i].vel_x = particles_new[i].vel_x;
      particles[i].vel_y = particles_new[i].vel_y;
    }
  }
  free(particles_new);
}

void print_array(particle_t* particles, int N)
{
  for(int i=0; i<N; i++) printf("%f ", particles[i].vel_y);
  putchar('\n');
}