#include <notcurses/notcurses.h>
#include <vector>
#include <iostream>
#include<pthread.h>
#include<time.h>
using namespace std;

unsigned int first_y, first_x,second_y,second_x,third_y,third_x;
int plane_number = 0;
struct shared_resources {

  struct ncplane* floating_plane[3];
  struct notcurses* nc_environ;
  pthread_mutex_t lock;
  int current_planeID; //0, 1, or 2
 
};

void* shrinking_box(void* _sh_res)
{
  struct shared_resources* res_ptr=(struct shared_resources*)_sh_res;

  int height,width,h_in,w_in;
 
	if(res_ptr->current_planeID ==0) height=first_y,width=first_x;
  else if(res_ptr->current_planeID ==1) height=second_y,width=second_x;
  else if(res_ptr->current_planeID ==2) height=third_y,width=third_x;

  int cursor_x = 0;
	int cursor_y = 0;
  uint64_t channel{0};
	ncchannels_set_fg_rgb8(&channel, 0xF0, 0xF0, 0xF0);



   h_in = height-1;
   w_in = width-1;

  while(1){

    pthread_mutex_lock(&res_ptr->lock);

		struct ncplane *current_plane = res_ptr->floating_plane[res_ptr->current_planeID];
    int temp_ht, temp_wt;
    	if(res_ptr->current_planeID ==0) temp_ht=first_y,temp_wt=first_x;
      if(res_ptr->current_planeID ==1) temp_ht=second_y,temp_wt=second_x;
      if(res_ptr->current_planeID ==2) temp_ht=third_y,temp_wt=third_x;

    if(height != temp_ht && width != temp_wt)
		{
			height = temp_ht;
			width = temp_wt;
			cursor_x = 0;
			cursor_y = 0;
			h_in = height-1;
			w_in = width-1;
		}

    ncplane_cursor_move_yx(current_plane, cursor_x, cursor_y);
		ncplane_rounded_box_sized(current_plane, 0, channel, h_in, w_in, 0);
		notcurses_render(res_ptr->nc_environ);

		ncplane_erase(current_plane);

  
    cursor_x += 1;
		cursor_y += 1;
		h_in-=2;
		w_in-=2;

		if (w_in <= 0 || h_in <= 0)
		{

			cursor_x = 0;
			cursor_y = 0;
			h_in = height-1;
			w_in = width-1;
		}


    pthread_mutex_unlock(&res_ptr->lock);

				
		struct timespec deadline;
		clock_gettime(CLOCK_MONOTONIC, &deadline);
		const uint64_t ONE_SECOND = 1000000000ull;
		deadline.tv_nsec += ONE_SECOND / 3;
		// Correct the time to account for the second boundary
		if (deadline.tv_nsec >= ONE_SECOND)
		{
			deadline.tv_nsec -= ONE_SECOND;
			++deadline.tv_sec;
		}
	

		while (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL) < 0)
		{
			if (errno != EINTR)
				return NULL;
		}

  }

  return nullptr;
}


int main()
{
  srand(time(NULL));
  notcurses_options ncopts{0};
  uint64_t channel{0};

  unsigned int red;
  unsigned int green;
  unsigned int blue;
  struct notcurses* nc_environ;

  nc_environ=notcurses_core_init(&ncopts,nullptr);

  struct ncplane* std_plane=notcurses_stdplane(nc_environ);

  nccell my_underlying_cell = NCCELL_CHAR_INITIALIZER(' ');
  nccell_set_bg_rgb8(&my_underlying_cell, 0x44, 0x11,0x44);

  ncplane_set_base_cell(std_plane, &my_underlying_cell);

  ncplane_set_bg_rgb8(std_plane, 0xFF,0xFF,0xFF);
  ncplane_set_bg_rgb8(std_plane, 0xFF,0xFF,0xFF);

  struct ncplane_options plane_opts{0};

  
  plane_opts.rows=5+rand()%20; plane_opts.cols=10+rand()%20;
  plane_opts.y=rand()%20; plane_opts.x=rand()%20;
  int height_first = plane_opts.rows-1 ;
  int weigth_first = plane_opts.cols-1;

  first_y=plane_opts.rows;
  first_x=plane_opts.cols;
  struct ncplane* first_plane=ncplane_create(std_plane, &plane_opts);
  int red_first = 0xFF;
  int blue_first = rand()%256;
  int green_first = rand()%256;

  // ncplane_dim_yx(first_plane, &first_y, &first_x);

  nccell_set_bg_rgb8(&my_underlying_cell, red_first, blue_first, green_first);
  
  ncplane_set_bg_rgb8(first_plane, red_first, blue_first, green_first);
  // ncplane_set_fg_rgb8(first_plane, red_first, blue_first, green_first);
  ncplane_set_base_cell(first_plane, &my_underlying_cell);



  plane_opts.rows=5+rand()%20; plane_opts.cols=10+rand()%20;
  plane_opts.y=rand()%20; plane_opts.x=rand()%20;
  int height_second = plane_opts.rows-1;
  int weigth_second = plane_opts.cols-1;
  second_y=plane_opts.rows;
  second_x=plane_opts.cols;
  struct ncplane* second_plane=ncplane_create(std_plane, &plane_opts);
  int red_second = rand()%256;
  int blue_second = 0xFF;
  int green_second = rand()%256;


  // ncplane_dim_yx(second_plane, &second_y, &second_x);


  nccell_set_bg_rgb8(&my_underlying_cell, red_second, blue_second, green_second);
 ncplane_set_bg_rgb8(second_plane, red_second, blue_second, green_second);

  ncplane_set_base_cell(second_plane, &my_underlying_cell);
  


  plane_opts.rows=5+rand()%20; plane_opts.cols=10+rand()%20;
  plane_opts.y=rand()%20; plane_opts.x=rand()%20;
  int height_third = plane_opts.rows-1;
  int weigth_third = plane_opts.cols-1;
  third_y=plane_opts.rows;
  third_x=plane_opts.cols;
  struct ncplane* third_plane=ncplane_create(std_plane, &plane_opts);
  int red_third = rand()%256;
  int blue_third = rand()%256;
  int green_third = 0xFF;
  nccell_set_bg_rgb8(&my_underlying_cell, red_third, blue_third, green_third);

  
  ncplane_set_bg_rgb8(third_plane, red_third, blue_third, green_third);
  ncplane_set_base_cell(third_plane, &my_underlying_cell);

  
 
  struct ncplane* current_plane;
  // if(randNum == 0) {
    current_plane = first_plane;
  
    red = red_first, blue = blue_first, green = green_first;
  // }
//   if(randNum == 1){
// current_plane = second_plane;

//     red = red_second, blue = blue_second, green = green_second;
//   } 
//   if(randNum == 2) {
//     current_plane = third_plane;
 
//     red = red_third, blue = blue_third, green = green_third;
//   }
  ncchannels_set_fg_rgb8(&channel, 0xff, 0x34, 0xee);
 
  struct ncinput input{0};

  struct shared_resources sh_res = {
	.floating_plane = {first_plane, second_plane, third_plane},
	.nc_environ = nc_environ,
	.lock = PTHREAD_MUTEX_INITIALIZER,
	.current_planeID = plane_number,
	};
  
  pthread_t tid;
	pthread_create(&tid, NULL, shrinking_box, &sh_res);



  do{
    notcurses_get_blocking(sh_res.nc_environ, &input);
    pthread_mutex_lock(&sh_res.lock);
    
    current_plane = sh_res.floating_plane[sh_res.current_planeID];


    if(input.id == 'j')
      ncplane_move_rel(current_plane, 1,0);
    if(input.id == 'k')
      ncplane_move_rel(current_plane, -1,0);
    if(input.id == 'h')
      ncplane_move_rel(current_plane, 0,-1);
    if(input.id == 'l')
      ncplane_move_rel(current_plane, 0,1);
    if(input.id == 'z')
      ncplane_move_top(current_plane);
    if(input.id == 'c'){
      red = rand()%256;
      blue = 0xFF;
      green = rand()%256;
      nccell_set_bg_rgb8(&my_underlying_cell,red, blue, green);
      ncplane_set_bg_rgb8(current_plane, red, blue, green);
      ncplane_set_fg_rgb8(current_plane, red, blue, green);
      ncplane_set_base_cell(current_plane, &my_underlying_cell);

    }
    if(input.id == ' '){


      
      plane_number++;
      if(plane_number>2) plane_number =0;
      if(plane_number == 0) {
    
        red = red_first;
        blue = blue_first; 
        green = green_first;
      }
      else if(plane_number == 1){
     
         red = red_second;
          blue = blue_second;
          green = green_second;
      } 
      else if(plane_number == 2) {
  
        red = red_third;
         blue = blue_third;
          green = green_third;
      }
      sh_res.current_planeID = plane_number;

    }

    notcurses_render(sh_res.nc_environ);
    pthread_mutex_unlock(&sh_res.lock);

  }while(input.id!='q');

  notcurses_stop(nc_environ);

 }
