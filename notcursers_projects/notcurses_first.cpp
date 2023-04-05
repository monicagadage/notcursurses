#include <notcurses/notcurses.h>
#include <vector>
int main()
{
  srand(time(NULL));
  notcurses_options ncopts{0};
  struct notcurses* nc_environ;

  nc_environ=notcurses_core_init(&ncopts,nullptr);

  struct ncplane* std_plane=notcurses_stdplane(nc_environ);

  nccell my_underlying_cell = NCCELL_CHAR_INITIALIZER(' ');
  nccell_set_bg_rgb8(&my_underlying_cell, 0x44, 0x11,0x44);

  ncplane_set_base_cell(std_plane, &my_underlying_cell);

  ncplane_set_fg_rgb8(std_plane, 0xFF,0xFF,0xFF);
  ncplane_set_fg_rgb8(std_plane, 0xFF,0xFF,0xFF);

  struct ncplane_options plane_opts{0};
  
  plane_opts.rows=3+rand()%20; plane_opts.cols=3+rand()%20;
  plane_opts.y=rand()%20; plane_opts.x=rand()%20;
  struct ncplane* first_plane=ncplane_create(std_plane, &plane_opts);
  nccell_set_bg_rgb8(&my_underlying_cell, 0xFF, rand()%256,rand()%256);
  ncplane_set_base_cell(first_plane, &my_underlying_cell);

  plane_opts.rows=3+rand()%20; plane_opts.cols=3+rand()%20;
  plane_opts.y=rand()%20; plane_opts.x=rand()%20;
  struct ncplane* second_plane=ncplane_create(std_plane, &plane_opts);
  nccell_set_bg_rgb8(&my_underlying_cell, rand()%256, rand()%256,0xFF);
  ncplane_set_base_cell(second_plane, &my_underlying_cell);

  plane_opts.rows=3+rand()%20; plane_opts.cols=3+rand()%20;
  plane_opts.y=rand()%20; plane_opts.x=rand()%20;
  struct ncplane* third_plane=ncplane_create(std_plane, &plane_opts);
  nccell_set_bg_rgb8(&my_underlying_cell, rand()%256, 0xFF,rand()%256);
  ncplane_set_base_cell(third_plane, &my_underlying_cell);

  
  
  int randNum = (rand() % 3) + 1;
  struct ncplane* current_plane;
  if(randNum == 1) current_plane = first_plane;
  if(randNum == 2) current_plane = second_plane;
  if(randNum == 3) current_plane = third_plane;
  

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
      nccell_set_bg_rgb8(&my_underlying_cell, rand()%256, 0xFF,rand()%256);
      ncplane_set_base_cell(current_plane, &my_underlying_cell);
    }
    if(input.id == ' '){
      int randNum = (rand() % 3) + 1;
      if(randNum == 1) current_plane = first_plane;
      if(randNum == 2) current_plane = second_plane;
      if(randNum == 3) current_plane = third_plane;
    }

    notcurses_render(nc_environ);
  }while(input.id!='q');

  notcurses_stop(nc_environ);

 }
