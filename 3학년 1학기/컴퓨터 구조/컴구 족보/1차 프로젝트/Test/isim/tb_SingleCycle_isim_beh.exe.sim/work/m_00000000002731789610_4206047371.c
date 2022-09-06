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
static const char *ng0 = "C:/workspace/Test/SEU.v";
static unsigned int ng1[] = {0U, 0U};
static int ng2[] = {15, 0};
static int ng3[] = {0, 0};
static int ng4[] = {31, 0};
static int ng5[] = {16, 0};
static unsigned int ng6[] = {1U, 0U};
static unsigned int ng7[] = {65535U, 0U};
static unsigned int ng8[] = {65535U, 65535U};



static void Always_28_0(char *t0)
{
    char t6[8];
    char t28[8];
    char t39[8];
    char t40[8];
    char t41[8];
    char t81[8];
    char t82[8];
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
    char *t42;
    char *t43;
    char *t44;
    char *t45;
    char *t46;
    char *t47;
    unsigned int t48;
    int t49;
    char *t50;
    unsigned int t51;
    int t52;
    int t53;
    char *t54;
    unsigned int t55;
    int t56;
    int t57;
    unsigned int t58;
    int t59;
    unsigned int t60;
    unsigned int t61;
    int t62;
    int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    char *t83;
    char *t84;
    char *t85;
    char *t86;
    unsigned int t87;
    char *t88;
    unsigned int t89;
    char *t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    unsigned int t94;

LAB0:    t1 = (t0 + 2528U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(28, ng0);
    t2 = (t0 + 2848);
    *((int *)t2) = 1;
    t3 = (t0 + 2560);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(28, ng0);

LAB5:    xsi_set_current_line(29, ng0);
    t4 = (t0 + 1208U);
    t5 = *((char **)t4);
    t4 = ((char*)((ng1)));
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

LAB11:    xsi_set_current_line(33, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng6)));
    memset(t6, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t9 = *((unsigned int *)t3);
    t10 = *((unsigned int *)t2);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t4);
    t13 = *((unsigned int *)t5);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB21;

LAB18:    if (t18 != 0)
        goto LAB20;

LAB19:    *((unsigned int *)t6) = 1;

LAB21:    t8 = (t6 + 4);
    t23 = *((unsigned int *)t8);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB22;

LAB23:    xsi_set_current_line(43, ng0);

LAB43:    xsi_set_current_line(44, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (t9 >> 0);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 0);
    *((unsigned int *)t2) = t12;
    t13 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t13 & 65535U);
    t14 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t14 & 65535U);
    t5 = (t0 + 1608);
    t7 = (t0 + 1608);
    t8 = (t7 + 72U);
    t21 = *((char **)t8);
    t22 = ((char*)((ng2)));
    t29 = ((char*)((ng3)));
    xsi_vlog_convert_partindices(t28, t39, t40, ((int*)(t21)), 2, t22, 32, 1, t29, 32, 1);
    t30 = (t28 + 4);
    t15 = *((unsigned int *)t30);
    t49 = (!(t15));
    t31 = (t39 + 4);
    t16 = *((unsigned int *)t31);
    t52 = (!(t16));
    t53 = (t49 && t52);
    t38 = (t40 + 4);
    t17 = *((unsigned int *)t38);
    t56 = (!(t17));
    t57 = (t53 && t56);
    if (t57 == 1)
        goto LAB44;

LAB45:    xsi_set_current_line(45, ng0);
    t2 = ((char*)((ng8)));
    t3 = (t0 + 1608);
    t4 = (t0 + 1608);
    t5 = (t4 + 72U);
    t7 = *((char **)t5);
    t8 = ((char*)((ng4)));
    t21 = ((char*)((ng5)));
    xsi_vlog_convert_partindices(t6, t28, t39, ((int*)(t7)), 2, t8, 32, 1, t21, 32, 1);
    t22 = (t6 + 4);
    t9 = *((unsigned int *)t22);
    t49 = (!(t9));
    t29 = (t28 + 4);
    t10 = *((unsigned int *)t29);
    t52 = (!(t10));
    t53 = (t49 && t52);
    t30 = (t39 + 4);
    t11 = *((unsigned int *)t30);
    t56 = (!(t11));
    t57 = (t53 && t56);
    if (t57 == 1)
        goto LAB46;

LAB47:
LAB24:
LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(29, ng0);

LAB13:    xsi_set_current_line(30, ng0);
    t29 = (t0 + 1048U);
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
    *((unsigned int *)t28) = (t36 & 65535U);
    t37 = *((unsigned int *)t29);
    *((unsigned int *)t29) = (t37 & 65535U);
    t38 = (t0 + 1608);
    t42 = (t0 + 1608);
    t43 = (t42 + 72U);
    t44 = *((char **)t43);
    t45 = ((char*)((ng2)));
    t46 = ((char*)((ng3)));
    xsi_vlog_convert_partindices(t39, t40, t41, ((int*)(t44)), 2, t45, 32, 1, t46, 32, 1);
    t47 = (t39 + 4);
    t48 = *((unsigned int *)t47);
    t49 = (!(t48));
    t50 = (t40 + 4);
    t51 = *((unsigned int *)t50);
    t52 = (!(t51));
    t53 = (t49 && t52);
    t54 = (t41 + 4);
    t55 = *((unsigned int *)t54);
    t56 = (!(t55));
    t57 = (t53 && t56);
    if (t57 == 1)
        goto LAB14;

LAB15:    xsi_set_current_line(31, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1608);
    t4 = (t0 + 1608);
    t5 = (t4 + 72U);
    t7 = *((char **)t5);
    t8 = ((char*)((ng4)));
    t21 = ((char*)((ng5)));
    xsi_vlog_convert_partindices(t6, t28, t39, ((int*)(t7)), 2, t8, 32, 1, t21, 32, 1);
    t22 = (t6 + 4);
    t9 = *((unsigned int *)t22);
    t49 = (!(t9));
    t29 = (t28 + 4);
    t10 = *((unsigned int *)t29);
    t52 = (!(t10));
    t53 = (t49 && t52);
    t30 = (t39 + 4);
    t11 = *((unsigned int *)t30);
    t56 = (!(t11));
    t57 = (t53 && t56);
    if (t57 == 1)
        goto LAB16;

LAB17:    goto LAB12;

LAB14:    t58 = *((unsigned int *)t41);
    t59 = (t58 + 0);
    t60 = *((unsigned int *)t39);
    t61 = *((unsigned int *)t40);
    t62 = (t60 - t61);
    t63 = (t62 + 1);
    xsi_vlogvar_wait_assign_value(t38, t28, t59, *((unsigned int *)t40), t63, 0LL);
    goto LAB15;

LAB16:    t12 = *((unsigned int *)t39);
    t59 = (t12 + 0);
    t13 = *((unsigned int *)t6);
    t14 = *((unsigned int *)t28);
    t62 = (t13 - t14);
    t63 = (t62 + 1);
    xsi_vlogvar_wait_assign_value(t3, t2, t59, *((unsigned int *)t28), t63, 0LL);
    goto LAB17;

LAB20:    t7 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB21;

LAB22:    xsi_set_current_line(33, ng0);

LAB25:    xsi_set_current_line(34, ng0);
    t21 = (t0 + 1048U);
    t22 = *((char **)t21);
    memset(t28, 0, 8);
    t21 = (t28 + 4);
    t29 = (t22 + 4);
    t32 = *((unsigned int *)t22);
    t33 = (t32 >> 15);
    t34 = (t33 & 1);
    *((unsigned int *)t28) = t34;
    t35 = *((unsigned int *)t29);
    t36 = (t35 >> 15);
    t37 = (t36 & 1);
    *((unsigned int *)t21) = t37;
    t30 = ((char*)((ng6)));
    memset(t39, 0, 8);
    t31 = (t28 + 4);
    t38 = (t30 + 4);
    t48 = *((unsigned int *)t28);
    t51 = *((unsigned int *)t30);
    t55 = (t48 ^ t51);
    t58 = *((unsigned int *)t31);
    t60 = *((unsigned int *)t38);
    t61 = (t58 ^ t60);
    t64 = (t55 | t61);
    t65 = *((unsigned int *)t31);
    t66 = *((unsigned int *)t38);
    t67 = (t65 | t66);
    t68 = (~(t67));
    t69 = (t64 & t68);
    if (t69 != 0)
        goto LAB29;

LAB26:    if (t67 != 0)
        goto LAB28;

LAB27:    *((unsigned int *)t39) = 1;

LAB29:    t43 = (t39 + 4);
    t70 = *((unsigned int *)t43);
    t71 = (~(t70));
    t72 = *((unsigned int *)t39);
    t73 = (t72 & t71);
    t74 = (t73 != 0);
    if (t74 > 0)
        goto LAB30;

LAB31:    xsi_set_current_line(38, ng0);

LAB38:    xsi_set_current_line(39, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (t9 >> 0);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 0);
    *((unsigned int *)t2) = t12;
    t13 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t13 & 65535U);
    t14 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t14 & 65535U);
    t5 = (t0 + 1608);
    t7 = (t0 + 1608);
    t8 = (t7 + 72U);
    t21 = *((char **)t8);
    t22 = ((char*)((ng2)));
    t29 = ((char*)((ng3)));
    xsi_vlog_convert_partindices(t28, t39, t40, ((int*)(t21)), 2, t22, 32, 1, t29, 32, 1);
    t30 = (t28 + 4);
    t15 = *((unsigned int *)t30);
    t49 = (!(t15));
    t31 = (t39 + 4);
    t16 = *((unsigned int *)t31);
    t52 = (!(t16));
    t53 = (t49 && t52);
    t38 = (t40 + 4);
    t17 = *((unsigned int *)t38);
    t56 = (!(t17));
    t57 = (t53 && t56);
    if (t57 == 1)
        goto LAB39;

LAB40:    xsi_set_current_line(40, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1608);
    t4 = (t0 + 1608);
    t5 = (t4 + 72U);
    t7 = *((char **)t5);
    t8 = ((char*)((ng4)));
    t21 = ((char*)((ng5)));
    xsi_vlog_convert_partindices(t6, t28, t39, ((int*)(t7)), 2, t8, 32, 1, t21, 32, 1);
    t22 = (t6 + 4);
    t9 = *((unsigned int *)t22);
    t49 = (!(t9));
    t29 = (t28 + 4);
    t10 = *((unsigned int *)t29);
    t52 = (!(t10));
    t53 = (t49 && t52);
    t30 = (t39 + 4);
    t11 = *((unsigned int *)t30);
    t56 = (!(t11));
    t57 = (t53 && t56);
    if (t57 == 1)
        goto LAB41;

LAB42:
LAB32:    goto LAB24;

LAB28:    t42 = (t39 + 4);
    *((unsigned int *)t39) = 1;
    *((unsigned int *)t42) = 1;
    goto LAB29;

LAB30:    xsi_set_current_line(34, ng0);

LAB33:    xsi_set_current_line(35, ng0);
    t44 = (t0 + 1048U);
    t45 = *((char **)t44);
    memset(t40, 0, 8);
    t44 = (t40 + 4);
    t46 = (t45 + 4);
    t75 = *((unsigned int *)t45);
    t76 = (t75 >> 0);
    *((unsigned int *)t40) = t76;
    t77 = *((unsigned int *)t46);
    t78 = (t77 >> 0);
    *((unsigned int *)t44) = t78;
    t79 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t79 & 65535U);
    t80 = *((unsigned int *)t44);
    *((unsigned int *)t44) = (t80 & 65535U);
    t47 = (t0 + 1608);
    t50 = (t0 + 1608);
    t54 = (t50 + 72U);
    t83 = *((char **)t54);
    t84 = ((char*)((ng2)));
    t85 = ((char*)((ng3)));
    xsi_vlog_convert_partindices(t41, t81, t82, ((int*)(t83)), 2, t84, 32, 1, t85, 32, 1);
    t86 = (t41 + 4);
    t87 = *((unsigned int *)t86);
    t49 = (!(t87));
    t88 = (t81 + 4);
    t89 = *((unsigned int *)t88);
    t52 = (!(t89));
    t53 = (t49 && t52);
    t90 = (t82 + 4);
    t91 = *((unsigned int *)t90);
    t56 = (!(t91));
    t57 = (t53 && t56);
    if (t57 == 1)
        goto LAB34;

LAB35:    xsi_set_current_line(36, ng0);
    t2 = ((char*)((ng7)));
    t3 = (t0 + 1608);
    t4 = (t0 + 1608);
    t5 = (t4 + 72U);
    t7 = *((char **)t5);
    t8 = ((char*)((ng4)));
    t21 = ((char*)((ng5)));
    xsi_vlog_convert_partindices(t6, t28, t39, ((int*)(t7)), 2, t8, 32, 1, t21, 32, 1);
    t22 = (t6 + 4);
    t9 = *((unsigned int *)t22);
    t49 = (!(t9));
    t29 = (t28 + 4);
    t10 = *((unsigned int *)t29);
    t52 = (!(t10));
    t53 = (t49 && t52);
    t30 = (t39 + 4);
    t11 = *((unsigned int *)t30);
    t56 = (!(t11));
    t57 = (t53 && t56);
    if (t57 == 1)
        goto LAB36;

LAB37:    goto LAB32;

LAB34:    t92 = *((unsigned int *)t82);
    t59 = (t92 + 0);
    t93 = *((unsigned int *)t41);
    t94 = *((unsigned int *)t81);
    t62 = (t93 - t94);
    t63 = (t62 + 1);
    xsi_vlogvar_wait_assign_value(t47, t40, t59, *((unsigned int *)t81), t63, 0LL);
    goto LAB35;

LAB36:    t12 = *((unsigned int *)t39);
    t59 = (t12 + 0);
    t13 = *((unsigned int *)t6);
    t14 = *((unsigned int *)t28);
    t62 = (t13 - t14);
    t63 = (t62 + 1);
    xsi_vlogvar_wait_assign_value(t3, t2, t59, *((unsigned int *)t28), t63, 0LL);
    goto LAB37;

LAB39:    t18 = *((unsigned int *)t40);
    t59 = (t18 + 0);
    t19 = *((unsigned int *)t28);
    t20 = *((unsigned int *)t39);
    t62 = (t19 - t20);
    t63 = (t62 + 1);
    xsi_vlogvar_wait_assign_value(t5, t6, t59, *((unsigned int *)t39), t63, 0LL);
    goto LAB40;

LAB41:    t12 = *((unsigned int *)t39);
    t59 = (t12 + 0);
    t13 = *((unsigned int *)t6);
    t14 = *((unsigned int *)t28);
    t62 = (t13 - t14);
    t63 = (t62 + 1);
    xsi_vlogvar_wait_assign_value(t3, t2, t59, *((unsigned int *)t28), t63, 0LL);
    goto LAB42;

LAB44:    t18 = *((unsigned int *)t40);
    t59 = (t18 + 0);
    t19 = *((unsigned int *)t28);
    t20 = *((unsigned int *)t39);
    t62 = (t19 - t20);
    t63 = (t62 + 1);
    xsi_vlogvar_wait_assign_value(t5, t6, t59, *((unsigned int *)t39), t63, 0LL);
    goto LAB45;

LAB46:    t12 = *((unsigned int *)t39);
    t59 = (t12 + 0);
    t13 = *((unsigned int *)t6);
    t14 = *((unsigned int *)t28);
    t62 = (t13 - t14);
    t63 = (t62 + 1);
    xsi_vlogvar_wait_assign_value(t3, t2, t59, *((unsigned int *)t28), t63, 0LL);
    goto LAB47;

}


extern void work_m_00000000002731789610_4206047371_init()
{
	static char *pe[] = {(void *)Always_28_0};
	xsi_register_didat("work_m_00000000002731789610_4206047371", "isim/tb_SingleCycle_isim_beh.exe.sim/work/m_00000000002731789610_4206047371.didat");
	xsi_register_executes(pe);
}
