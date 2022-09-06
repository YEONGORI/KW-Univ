/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/workspace/Test/IM.v";
static const char *ng1 = "machinecode.txt";
static int ng2[] = {3, 0};
static int ng3[] = {7, 0};
static int ng4[] = {0, 0};
static int ng5[] = {2, 0};
static int ng6[] = {15, 0};
static int ng7[] = {8, 0};
static int ng8[] = {1, 0};
static int ng9[] = {23, 0};
static int ng10[] = {16, 0};
static int ng11[] = {31, 0};
static int ng12[] = {24, 0};



static void Initial_28_0(char *t0)
{
    char *t1;

LAB0:    xsi_set_current_line(28, ng0);

LAB2:    xsi_set_current_line(29, ng0);
    t1 = (t0 + 1608);
    xsi_vlogfile_readmemb(ng1, 0, t1, 0, 0, 0, 0);

LAB1:    return;
}

static void Always_32_1(char *t0)
{
    char t7[8];
    char t16[8];
    char t18[8];
    char t19[8];
    char t20[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t17;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned int t27;
    int t28;
    char *t29;
    unsigned int t30;
    int t31;
    int t32;
    char *t33;
    unsigned int t34;
    int t35;
    int t36;
    unsigned int t37;
    int t38;
    unsigned int t39;
    unsigned int t40;
    int t41;
    int t42;

LAB0:    t1 = (t0 + 2776U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(32, ng0);
    t2 = (t0 + 3096);
    *((int *)t2) = 1;
    t3 = (t0 + 2808);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(32, ng0);

LAB5:    xsi_set_current_line(33, ng0);
    t4 = (t0 + 1608);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t8 = (t0 + 1608);
    t9 = (t8 + 72U);
    t10 = *((char **)t9);
    t11 = (t0 + 1608);
    t12 = (t11 + 64U);
    t13 = *((char **)t12);
    t14 = (t0 + 1048U);
    t15 = *((char **)t14);
    t14 = ((char*)((ng2)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t15, 32, t14, 32);
    xsi_vlog_generic_get_array_select_value(t7, 8, t6, t10, t13, 2, 1, t16, 32, 2);
    t17 = (t0 + 1448);
    t21 = (t0 + 1448);
    t22 = (t21 + 72U);
    t23 = *((char **)t22);
    t24 = ((char*)((ng3)));
    t25 = ((char*)((ng4)));
    xsi_vlog_convert_partindices(t18, t19, t20, ((int*)(t23)), 2, t24, 32, 1, t25, 32, 1);
    t26 = (t18 + 4);
    t27 = *((unsigned int *)t26);
    t28 = (!(t27));
    t29 = (t19 + 4);
    t30 = *((unsigned int *)t29);
    t31 = (!(t30));
    t32 = (t28 && t31);
    t33 = (t20 + 4);
    t34 = *((unsigned int *)t33);
    t35 = (!(t34));
    t36 = (t32 && t35);
    if (t36 == 1)
        goto LAB6;

LAB7:    xsi_set_current_line(34, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1608);
    t6 = (t5 + 72U);
    t8 = *((char **)t6);
    t9 = (t0 + 1608);
    t10 = (t9 + 64U);
    t11 = *((char **)t10);
    t12 = (t0 + 1048U);
    t13 = *((char **)t12);
    t12 = ((char*)((ng5)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t13, 32, t12, 32);
    xsi_vlog_generic_get_array_select_value(t7, 8, t4, t8, t11, 2, 1, t16, 32, 2);
    t14 = (t0 + 1448);
    t15 = (t0 + 1448);
    t17 = (t15 + 72U);
    t21 = *((char **)t17);
    t22 = ((char*)((ng6)));
    t23 = ((char*)((ng7)));
    xsi_vlog_convert_partindices(t18, t19, t20, ((int*)(t21)), 2, t22, 32, 1, t23, 32, 1);
    t24 = (t18 + 4);
    t27 = *((unsigned int *)t24);
    t28 = (!(t27));
    t25 = (t19 + 4);
    t30 = *((unsigned int *)t25);
    t31 = (!(t30));
    t32 = (t28 && t31);
    t26 = (t20 + 4);
    t34 = *((unsigned int *)t26);
    t35 = (!(t34));
    t36 = (t32 && t35);
    if (t36 == 1)
        goto LAB8;

LAB9:    xsi_set_current_line(35, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1608);
    t6 = (t5 + 72U);
    t8 = *((char **)t6);
    t9 = (t0 + 1608);
    t10 = (t9 + 64U);
    t11 = *((char **)t10);
    t12 = (t0 + 1048U);
    t13 = *((char **)t12);
    t12 = ((char*)((ng8)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t13, 32, t12, 32);
    xsi_vlog_generic_get_array_select_value(t7, 8, t4, t8, t11, 2, 1, t16, 32, 2);
    t14 = (t0 + 1448);
    t15 = (t0 + 1448);
    t17 = (t15 + 72U);
    t21 = *((char **)t17);
    t22 = ((char*)((ng9)));
    t23 = ((char*)((ng10)));
    xsi_vlog_convert_partindices(t18, t19, t20, ((int*)(t21)), 2, t22, 32, 1, t23, 32, 1);
    t24 = (t18 + 4);
    t27 = *((unsigned int *)t24);
    t28 = (!(t27));
    t25 = (t19 + 4);
    t30 = *((unsigned int *)t25);
    t31 = (!(t30));
    t32 = (t28 && t31);
    t26 = (t20 + 4);
    t34 = *((unsigned int *)t26);
    t35 = (!(t34));
    t36 = (t32 && t35);
    if (t36 == 1)
        goto LAB10;

LAB11:    xsi_set_current_line(36, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1608);
    t6 = (t5 + 72U);
    t8 = *((char **)t6);
    t9 = (t0 + 1608);
    t10 = (t9 + 64U);
    t11 = *((char **)t10);
    t12 = (t0 + 1048U);
    t13 = *((char **)t12);
    xsi_vlog_generic_get_array_select_value(t7, 8, t4, t8, t11, 2, 1, t13, 32, 2);
    t12 = (t0 + 1448);
    t14 = (t0 + 1448);
    t15 = (t14 + 72U);
    t17 = *((char **)t15);
    t21 = ((char*)((ng11)));
    t22 = ((char*)((ng12)));
    xsi_vlog_convert_partindices(t16, t18, t19, ((int*)(t17)), 2, t21, 32, 1, t22, 32, 1);
    t23 = (t16 + 4);
    t27 = *((unsigned int *)t23);
    t28 = (!(t27));
    t24 = (t18 + 4);
    t30 = *((unsigned int *)t24);
    t31 = (!(t30));
    t32 = (t28 && t31);
    t25 = (t19 + 4);
    t34 = *((unsigned int *)t25);
    t35 = (!(t34));
    t36 = (t32 && t35);
    if (t36 == 1)
        goto LAB12;

LAB13:    goto LAB2;

LAB6:    t37 = *((unsigned int *)t20);
    t38 = (t37 + 0);
    t39 = *((unsigned int *)t18);
    t40 = *((unsigned int *)t19);
    t41 = (t39 - t40);
    t42 = (t41 + 1);
    xsi_vlogvar_wait_assign_value(t17, t7, t38, *((unsigned int *)t19), t42, 0LL);
    goto LAB7;

LAB8:    t37 = *((unsigned int *)t20);
    t38 = (t37 + 0);
    t39 = *((unsigned int *)t18);
    t40 = *((unsigned int *)t19);
    t41 = (t39 - t40);
    t42 = (t41 + 1);
    xsi_vlogvar_wait_assign_value(t14, t7, t38, *((unsigned int *)t19), t42, 0LL);
    goto LAB9;

LAB10:    t37 = *((unsigned int *)t20);
    t38 = (t37 + 0);
    t39 = *((unsigned int *)t18);
    t40 = *((unsigned int *)t19);
    t41 = (t39 - t40);
    t42 = (t41 + 1);
    xsi_vlogvar_wait_assign_value(t14, t7, t38, *((unsigned int *)t19), t42, 0LL);
    goto LAB11;

LAB12:    t37 = *((unsigned int *)t19);
    t38 = (t37 + 0);
    t39 = *((unsigned int *)t16);
    t40 = *((unsigned int *)t18);
    t41 = (t39 - t40);
    t42 = (t41 + 1);
    xsi_vlogvar_wait_assign_value(t12, t7, t38, *((unsigned int *)t18), t42, 0LL);
    goto LAB13;

}


extern void work_m_00000000002407872904_0467708899_init()
{
	static char *pe[] = {(void *)Initial_28_0,(void *)Always_32_1};
	xsi_register_didat("work_m_00000000002407872904_0467708899", "isim/tb_SingleCycle_isim_beh.exe.sim/work/m_00000000002407872904_0467708899.didat");
	xsi_register_executes(pe);
}
