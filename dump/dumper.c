
static void	split_img(t_shaders **imgx, t_vec3 wh, int i)
{
	t_vec4	ifr;
	t_vec2	adr;

	ifr.x = i * wh.x;
	ifr.y = 0;
	while (ifr.y < wh.y)
	{
		ifr.z = 0;
		ifr.w = ifr.x + ifr.z;
		while (ifr.w < ifr.x + wh.x)
		{
			adr.x = ifr.y * imgx[0]->img.len + ifr.w * (imgx[0]->img.bpp / 8);
			adr.y = ifr.y * imgx[1]->img.len + ifr.z * (imgx[1]->img.bpp / 8);
			set_value(imgx[1]->img.addr + adr.y, 0);
			if (get_value(imgx[0]->img.addr + adr.x) != 0xFF000000)
				set_value(imgx[1]->img.addr + adr.y,
					get_value(imgx[0]->img.addr + adr.x));
			ifr.z++;
			ifr.w = ifr.x + ifr.z;
		}
		ifr.y++;
	}
}

void	split_asset(void)
{
	t_shaders	tmps;
	t_shaders	*imgx[2];
	int			i;
	char		tmp[19];
	char		cm[100];
	int			fd;

	register_img("./textures/hands/hand_anim_001.xpm");
	imgx[0] = get_img("/hand_anim_001.xpm");
	imgx[1] = get_img("dump_hand");
	i = 0;
	xmemset(cm, 0, 100);
	xmemcpy(tmp, "", 18);
	xmemcpy(cm, "./dump/hand_anim_000.bin", 25);
	while (i < (imgx[0]->img.width / imgx[1]->img.width))
	{
		split_img(imgx, (t_vec3){imgx[1]->img.width, imgx[1]->img.height, 0}, i);
		cm[17] = 0x30 + (i / 100);
		cm[18] = 0x30 + ((i / 10) % 10);
		cm[19] = 0x30 + (i % 10);
		print_img((t_vec2){355, 400}, "dump_hand");
		sleep(1);
		printf("%s\n",cm);
		fd = open(cm, O_CREAT | O_WRONLY, 777);
		if (fd > 0)
		{
			xmemcpy(&tmps, get_img("dump_hand"), sizeof(t_shaders));
			tmps.img.ptr
			
			write(fd, &get_img("dump_hand")->img.addr[0], sizeof(get_img("dump_hand")->img.addr[0]));
			close(fd);
		}
		i++;
	}
}
