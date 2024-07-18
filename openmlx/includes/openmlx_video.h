/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_video.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:33:02 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/27 20:13:33 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_VIDEO_H
# define OPENMLX_VIDEO_H

enum e_video
{
	VIDEO_RESUME	= 0,
	VIDEO_PAUSE
};

typedef struct rec_s
{
	int					fd;
	int					status;
	int					rate;
	char				buffer[128];
	char				tracked[128];
	unsigned long int	size;
}	t_rec;

typedef struct video_s
{
	int		fd;
	int		status;
	int		rate;
	int		paused;
	char	buffer[128];
}	t_video;

//record
void	init_record(char *export_file, char *track_img, int rate);
void	save_record(void);
void	stop_record(void);
//display video
void	display_video(t_vec2 at);
void	stop_video(void);
void	set_video_status(int pause);
void	start_video(char *name, int rate);
#endif