/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:49:16 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 22:02:22 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include "./libft/libft.h"

typedef	struct	s_flags
{
	int			j;
	int			ll;
	int			l;
	int			h;
	int			hh;
	int			hash;
	int			zflag;
	int			mflag;
	int			sign;
	int			space;
	int			precision;
	int			isnegative;
	int			zero;
	int			conid;
	int			size;
	int			extra;
	char		*ret;
}				t_flags;

extern char		*g_format;
extern void		(*g_gl[14])(va_list *ptr, t_flags **flag);
void			finish(char *format, t_flags **flag, int *index, va_list *args);
void			doelse(char *format, t_flags **flag, int *index);
void			moreish(char *format, t_flags **flag, int *index);
void			domore(char *format, t_flags **flag, int *index, va_list *args);
int				morecontin(char *format, int findex);
int				flagcontin(char *format, int findex);
int				contin(char *format, int findex);
int				findfunind(char c);
void			pf_putstr(va_list *ptr, t_flags **flag);
void			pf_putnbr(va_list *args, t_flags **flag);
void			pf_putchar(va_list *args, t_flags **flag);
void			pf_x_handle(va_list *args, t_flags **flag);
void			pf_xlow_handle(va_list *args, t_flags **flag);
void			pf_o_handle(va_list *args, t_flags **flag);
void			pf_oup_handle(va_list *args, t_flags **flag);
void			pf_p_handle(va_list *args, t_flags **flag);
void			pf_u_handle(va_list *args, t_flags **flag);
void			pf_uup_handle(va_list *args, t_flags **flag);
void			pf_dup_handle(va_list *args, t_flags **flag);
int				findsize(uintmax_t value, int base);
char			*betterjoin(char *first, char *second);
char			*charadder(char *str, char c);
char			*ft_itoa_baseint(intmax_t value, int base);
uintmax_t		ft_pow(uintmax_t nb, int pow);
char			*ft_itoa_base(ssize_t value, int base);
char			*ft_itoa_baselow(ssize_t value, intmax_t base);
char			*ft_itoa_baseuint(uintmax_t value, int base);
char			*ft_itoa_baselowuint(uintmax_t value, int base);
char			*ft_itoa_baselowu(uintmax_t value, uintmax_t base);
char			*ft_itoa_baseu(uintmax_t value, uintmax_t base);
void			setflags(t_flags **flag);
void			setsymb(t_flags **flag, int *findex, const char *format);
void			findflags(t_flags **flag, int *findex, const char *format);
int				checkzeroflag(t_flags **flag);
int				findprecision(const char *format, int *findex);
int				findprecisionspace(const char *format, int *findex);
int				findprecisionextra(const char *format, int *findex);
int				checkoptions(t_flags **flag);
char			*flagformatingstrings(char *str, t_flags **flag);
int				findprecision(const char *format, int *findex);
char			*flagformating(char *str, t_flags **flag);
void			isnegative(t_flags **flag, intmax_t data);
char			*makespace(int size, int c);
char			*percisionflag(char *str, char *temp, t_flags **flag);
char			*signflag(char *str, char *temp, t_flags **flag);
char			*spaceflag(char *str, char *temp, t_flags **flag);
char			*zeroflag(char *str, char *temp, t_flags **flag);
char			*hashflag(char *str, char *temp, t_flags **flag);
char			*extraflag(char *str, char *temp, t_flags **flag);
char			*mflag(char *str, char *temp, t_flags **flag);
char			*stringpercision(char *str, char *temp, t_flags **flag);
char			*stringmflag(char *str, char *temp, t_flags **flag);
char			*strspace(char *str, char *temp, t_flags **flag);
char			*percdealer(t_flags **flag);
int				ft_printf(const char *format, ...);
char			*zerostr(char *str, char *temp, t_flags **flag);
char			*signflagstr(char *str, char *temp, t_flags **flag);
int				findhash(const char *format, int *findex);
char			*helpit(char *ret, long *in, intmax_t *isize, int base);
char			*spaceextra(char *str, char *temp, t_flags *tempflag, char *t);
#endif
