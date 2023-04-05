#include <notcurses/notcurses.h>
#include <vector>
#include <iostream>
using namespace std;
int main()
{
  srand(time(NULL));
  notcurses_options ncopts{0};
  uint64_t channel{0};
  int height;
  int width;
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

  
  plane_opts.rows=3+rand()%20; plane_opts.cols=3+rand()%20;
  plane_opts.y=rand()%20; plane_opts.x=rand()%20;
  int height_first = plane_opts.rows-1 ;
  int weigth_first = plane_opts.cols-1;
  struct ncplane* first_plane=ncplane_create(std_plane, &plane_opts);
  int red_first = 0xFF;
  int blue_first = rand()%256;
  int green_first = rand()%256;
  nccell_set_bg_rgb8(&my_underlying_cell, red_first, blue_first, green_first);
     ncplane_set_bg_rgb8(first_plane, red_first, blue_first, green_first);
       ncplane_set_fg_rgb8(first_plane, red_first, blue_first, green_first);
  ncplane_set_base_cell(first_plane, &my_underlying_cell);



  plane_opts.rows=3+rand()%20; plane_opts.cols=3+rand()%20;
  plane_opts.y=rand()%20; plane_opts.x=rand()%20;
  int height_second = plane_opts.rows-1;
  int weigth_second = plane_opts.cols-1;
  struct ncplane* second_plane=ncplane_create(std_plane, &plane_opts);
  int red_second = rand()%256;
  int blue_second = 0xFF;
  int green_second = rand()%256;
  nccell_set_bg_rgb8(&my_underlying_cell, red_second, blue_second, green_second);
 ncplane_set_bg_rgb8(second_plane, red_second, blue_second, green_second);
 ncplane_set_fg_rgb8(second_plane, red_second, blue_second, green_second);
  ncplane_set_base_cell(second_plane, &my_underlying_cell);
  


  plane_opts.rows=3+rand()%20; plane_opts.cols=3+rand()%20;
  plane_opts.y=rand()%20; plane_opts.x=rand()%20;
  int height_third = plane_opts.rows-1;
  int weigth_third = plane_opts.cols-1;
  struct ncplane* third_plane=ncplane_create(std_plane, &plane_opts);
  int red_third = rand()%256;
  int blue_third = rand()%256;
  int green_third = 0xFF;
  nccell_set_bg_rgb8(&my_underlying_cell, red_third, blue_third, green_third);
  
  
  ncplane_set_bg_rgb8(third_plane, red_third, blue_third, green_third);
  ncplane_set_fg_rgb8(third_plane, red_third, blue_third, green_third);
  ncplane_set_base_cell(third_plane, &my_underlying_cell);

  
  
  int randNum = (rand() % 3) + 1;
  struct ncplane* current_plane;
  if(randNum == 1) {
    current_plane = first_plane;
    height = height_first;
    width = weigth_first;
    red = red_first, blue = blue_first, green = green_first;
  }
  if(randNum == 2){
current_plane = second_plane;
height = height_second;
    width = weigth_second;
    red = red_second, blue = blue_second, green = green_second;
  } 
  if(randNum == 3) {
    current_plane = third_plane;
    height = height_third;
    width = weigth_third;
    red = red_third, blue = blue_third, green = green_third;
  }
  ncchannels_set_fg_rgb8(&channel, 0xff, 0x34, 0xee);
  ncplane_perimeter_rounded(current_plane, 0, channel, 0);

  notcurses_render(nc_environ);
  struct ncinput input{0};
  do{
    notcurses_get_blocking(nc_environ, &input);
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
      ncplane_bg_rgb8(current_plane, &red, &blue, &green);
      ncchannels_set_fg_rgb8(&channel, red, blue, green);
      ncplane_perimeter_rounded(current_plane, 0, channel, 0);
      nccell_set_bg_rgb8(&my_underlying_cell, red, blue, green);
      ncplane_set_base_cell(current_plane, &my_underlying_cell);

      int randNum = (rand() % 3) + 1;
      if(randNum == 1) {
        current_plane = first_plane;
        height = height_first;
        width = weigth_first;
        red = red_first;
        blue = blue_first; 
        green = green_first;
      }
      if(randNum == 2){
        current_plane = second_plane;
        height = height_second;
        width = weigth_second;
         red = red_second;
          blue = blue_second;
          green = green_second;
      } 
      if(randNum == 3) {
        current_plane = third_plane;
        height = height_third;
        width = weigth_third;
        red = red_third;
         blue = blue_third;
          green = green_third;
      }
    
        ncchannels_set_fg_rgb8(&channel, 0xff, 0x34, 0xee);
        ncplane_perimeter_rounded(current_plane, 0, channel, 0);

    }

    notcurses_render(nc_environ);
  }while(input.id!='q');

  notcurses_stop(nc_environ);

 }
