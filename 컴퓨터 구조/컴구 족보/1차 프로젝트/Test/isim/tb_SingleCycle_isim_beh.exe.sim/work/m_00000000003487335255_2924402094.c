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
static const char *ng0 = "C:/workspace/Test/DM.v";
static const char *ng1 = "data_memory.txt";
static unsigned int ng2[] = {1U, 0U};
static int ng3[] = {3, 0};
static int ng4[] = {2, 0};
static int ng5[] = {1, 0};
static int ng6[] = {7, 0};
static int ng7[] = {0, 0};
static int ng8[] = {15, 0};
static int ng9[] = {8, 0};
static int ng10[] = {23, 0};
static int ng11[] = {16, 0};
static int ng12[] = {31, 0};
static int ng13[] = {24, 0};



static void Initial_30_0(char *t0)
{
    char *t1;

LAB0:    xsi_set_current_line(30, ng0);

LAB2:    xsi_set_current_line(31, ng0);
    t1 = (t0 + 2088);
    xsi_vlogfile_readmemb(ng1, 0, t1, 0, 0, 0, 0);

LAB1:    return;
}

static void Always_34_1(char *t0)
{
    char t6[8];
    char t28[8];
    char t39[8];
    char t40[8];
    char t49[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t29;
    char *t30;
    char *t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    char *t38;
    char *t41;
    char *t42;
    char *t43;
    char *t44;
    char *t45;
    char *t46;
    char *t47;
    char *t48;
    char *t50;
    unsigned int t51;
    int t52;
    char *t53;
    unsigned int t54;
    int t55;
    int t56;
    unsigned int t57;
    unsigned int t58;
    int t59;
    int t60;

LAB0:    t1 = (t0 + 3256U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(34, ng0);
    t2 = (t0 + 3824);
    *((int *)t2) = 1;
    t3 = (t0 + 3288);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(34, ng0);

LAB5:    xsi_set_current_line(35, ng0);
    t4 = (t0 + 1208U);
    t5 = *((char **)t4);
    t4 = ((char*)((ng2)));
    memset(t6, 0, 8);
    t7 = (t5 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t4);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB9;

LAB6:    if (t18 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t6) = 1;

LAB9:    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB10;

LAB11:
LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(35, ng0);

LAB13:    xsi_set_current_line(36, ng0);
    t29 = (t0 + 1528U);
    t30 = *((char **)t29);
    memset(t28, 0, 8);
    t29 = (t28 + 4);
    t31 = (t30 + 4);
    t32 = *((unsigned int *)t30);
    t33 = (t32 >> 0);
    *((unsigned int *)t28) = t33;
    t34 = *((unsigned int *)t31);
    t35 = (t34 >> 0);
    *((unsigned int *)t29) = t35;
    t36 = *((unsigned int *)t28);
    *((unsigned int *)t28) = (t36 & 255U);
    t37 = *((unsigned int *)t29);
    *((unsigned int *)t29) = (t37 & 255U);
    t38 = (t0 + 2088);
    t41 = (t0 + 2088);
    t42 = (t41 + 72U);
    t43 = *((char **)t42);
    t44 = (t0 + 2088);
    t45 = (t44 + 64U);
    t46 = *((char **)t45);
    t47 = (t0 + 1368U);
    t48 = *((char **)t47);
    t47 = ((char*)((ng3)));
    memset(t49, 0, 8);
    xsi_vlog_unsigned_add(t49, 32, t48, 32, t47, 32);
    xsi_vlog_generic_convert_array_indices(t39, t40, t43, t46, 2, 1, t49, 32, 2);
    t50 = (t39 + 4);
    t51 = *((unsigned int *)t50);
    t52 = (!(t51));
    t53 = (t40 + 4);
    t54 = *((unsigned int *)t53);
    t55 = (!(t54));
    t56 = (t52 && t55);
    if (t56 == 1)
        goto LAB14;

LAB15:    xsi_set_current_line(37, ng0);
    t2 = (t0 + 1528U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (t9 >> 8);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 8);
    *((unsigned int *)t2) = t12;
    t13 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t13 & 255U);
    t14 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t14 & 255U);
    t5 = (t0 + 2088);
    t7 = (t0 + 2088);
    t8 = (t7 + 72U);
    t21 = *((char **)t8);
    t22 = (t0 + 2088);
    t29 = (t22 + 64U);
    t30 = *((char **)t29);
    t31 = (t0 + 1368U);
    t38 = *((char **)t31);
    t31 = ((char*)((ng4)));
    memset(t40, 0, 8);
    xsi_vlog_unsigned_add(t40, 32, t38, 32, t31, 32);
    xsi_vlog_generic_convert_array_indices(t28, t39, t21, t30, 2, 1, t40, 32, 2);
    t41 = (t28 + 4);
    t15 = *((unsigned int *)t41);
    t52 = (!(t15));
    t42 = (t39 + 4);
    t16 = *((unsigned int *)t42);
    t55 = (!(t16));
    t56 = (t52 && t55);
    if (t56 == 1)
        goto LAB16;

LAB17:    xsi_set_current_line(38, ng0);
    t2 = (t0 + 1528U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (t9 >> 16);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 16);
    *((unsigned int *)t2) = t12;
    t13 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t13 & 255U);
    t14 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t14 & 255U);
    t5 = (t0 + 2088);
    t7 = (t0 + 2088);
    t8 = (t7 + 72U);
    t21 = *((char **)t8);
    t22 = (t0 + 2088);
    t29 = (t22 + 64U);
    t30 = *((char **)t29);
    t31 = (t0 + 1368U);
    t38 = *((char **)t31);
    t31 = ((char*)((ng5)));
    memset(t40, 0, 8);
    xsi_vlog_unsigned_add(t40, 32, t38, 32, t31, 32);
    xsi_vlog_generic_convert_array_indices(t28, t39, t21, t30, 2, 1, t40, 32, 2);
    t41 = (t28 + 4);
    t15 = *((unsigned int *)t41);
    t52 = (!(t15));
    t42 = (t39 + 4);
    t16 = *((unsigned int *)t42);
    t55 = (!(t16));
    t56 = (t52 && t55);
    if (t56 == 1)
        goto LAB18;

LAB19:    xsi_set_current_line(39, ng0);
    t2 = (t0 + 1528U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (t9 >> 24);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 24);
    *((unsigned int *)t2) = t12;
    t13 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t13 & 255U);
    t14 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t14 & 255U);
    t5 = (t0 + 2088);
    t7 = (t0 + 2088);
    t8 = (t7 + 72U);
    t21 = *((char **)t8);
    t22 = (t0 + 2088);
    t29 = (t22 + 64U);
    t30 = *((char **)t29);
    t31 = (t0 + 1368U);
    t38 = *((char **)t31);
    xsi_vlog_generic_convert_array_indices(t28, t39, t21, t30, 2, 1, t38, 32, 2);
    t31 = (t28 + 4);
    t15 = *((unsigned int *)t31);
    t52 = (!(t15));
    t41 = (t39 + 4);
    t16 = *((unsigned int *)t41);
    t55 = (!(t16));
    t56 = (t52 && t55);
    if (t56 == 1)
        goto LAB20;

LAB21:    goto LAB12;

LAB14:    t57 = *((unsigned int *)t39);
    t58 = *((unsigned int *)t40);
    t59 = (t57 - t58);
    t60 = (t59 + 1);
    xsi_vlogvar_wait_assign_value(t38, t28, 0, *((unsigned int *)t40), t60, 0LL);
    goto LAB15;

LAB16:    t17 = *((unsigned int *)t28);
    t18 = *((unsigned int *)t39);
    t59 = (t17 - t18);
    t60 = (t59 + 1);
    xsi_vlogvar_wait_assign_value(t5, t6, 0, *((unsigned int *)t39), t60, 0LL);
    goto LAB17;

LAB18:    t17 = *((unsigned int *)t28);
    t18 = *((unsigned int *)t39);
    t59 = (t17 - t18);
    t60 = (t59 + 1);
    xsi_vlogvar_wait_assign_value(t5, t6, 0, *((unsigned int *)t39), t60, 0LL);
    goto LAB19;

LAB20:    t17 = *((unsigned int *)t28);
    t18 = *((unsigned int *)t39);
    t59 = (t17 - t18);
    t60 = (t59 + 1);
    xsi_vlogvar_wait_assign_value(t5, t6, 0, *((unsigned int *)t39), t60, 0LL);
    goto LAB21;

}

static void Always_43_2(char *t0)
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

LAB0:    t1 = (t0 + 3504U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(43, ng0);
    t2 = (t0 + 3840);
    *((int *)t2) = 1;
    t3 = (t0 + 3536);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(43, ng0);

LAB5:    xsi_set_current_line(44, ng0);
    t4 = (t0 + 2088);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t8 = (t0 + 2088);
    t9 = (t8 + 72U);
    t10 = *((char **)t9);
    t11 = (t0 + 2088);
    t12 = (t11 + 64U);
    t13 = *((char **)t12);
    t14 = (t0 + 1368U);
    t15 = *((char **)t14);
    t14 = ((char*)((ng3)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t15, 32, t14, 32);
    xsi_vlog_generic_get_array_select_value(t7, 8, t6, t10, t13, 2, 1, t16, 32, 2);
    t17 = (t0 + 1928);
    t21 = (t0 + 1928);
    t22 = (t21 + 72U);
    t23 = *((char **)t22);
    t24 = ((char*)((ng6)));
    t25 = ((char*)((ng7)));
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

LAB7:    xsi_set_current_line(45, ng0);
    t2 = (t0 + 2088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2088);
    t6 = (t5 + 72U);
    t8 = *((char **)t6);
    t9 = (t0 + 2088);
    t10 = (t9 + 64U);
    t11 = *((char **)t10);
    t12 = (t0 + 1368U);
    t13 = *((char **)t12);
    t12 = ((char*)((ng4)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t13, 32, t12, 32);
    xsi_vlog_generic_get_array_select_value(t7, 8, t4, t8, t11, 2, 1, t16, 32, 2);
    t14 = (t0 + 1928);
    t15 = (t0 + 1928);
    t17 = (t15 + 72U);
    t21 = *((char **)t17);
    t22 = ((char*)((ng8)));
    t23 = ((char*)((ng9)));
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

LAB9:    xsi_set_current_line(46, ng0);
    t2 = (t0 + 2088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2088);
    t6 = (t5 + 72U);
    t8 = *((char **)t6);
    t9 = (t0 + 2088);
    t10 = (t9 + 64U);
    t11 = *((char **)t10);
    t12 = (t0 + 1368U);
    t13 = *((char **)t12);
    t12 = ((char*)((ng5)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t13, 32, t12, 32);
    xsi_vlog_generic_get_array_select_value(t7, 8, t4, t8, t11, 2, 1, t16, 32, 2);
    t14 = (t0 + 1928);
    t15 = (t0 + 1928);
    t17 = (t15 + 72U);
    t21 = *((char **)t17);
    t22 = ((char*)((ng10)));
    t23 = ((char*)((ng11)));
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

LAB11:    xsi_set_current_line(47, ng0);
    t2 = (t0 + 2088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2088);
    t6 = (t5 + 72U);
    t8 = *((char **)t6);
    t9 = (t0 + 2088);
    t10 = (t9 + 64U);
    t11 = *((char **)t10);
    t12 = (t0 + 1368U);
    t13 = *((char **)t12);
    xsi_vlog_generic_get_array_select_value(t7, 8, t4, t8, t11, 2, 1, t13, 32, 2);
    t12 = (t0 + 1928);
    t14 = (t0 + 1928);
    t15 = (t14 + 72U);
    t17 = *((char **)t15);
    t21 = ((char*)((ng12)));
    t22 = ((char*)((ng13)));
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


extern void work_m_00000000003487335255_2924402094_init()
{
	static char *pe[] = {(void *)Initial_30_0,(void *)Always_34_1,(void *)Always_43_2};
	xsi_register_didat("work_m_00000000003487335255_2924402094", "isim/tb_SingleCycle_isim_beh.exe.sim/work/m_00000000003487335255_2924402094.didat");
	xsi_register_executes(pe);
}
