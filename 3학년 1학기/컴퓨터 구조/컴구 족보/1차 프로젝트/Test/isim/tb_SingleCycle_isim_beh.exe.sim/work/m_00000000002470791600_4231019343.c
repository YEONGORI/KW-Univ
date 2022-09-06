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
static const char *ng0 = "C:/workspace/Test/ALUControl.v";
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {2U, 0U};
static unsigned int ng3[] = {1U, 0U};
static unsigned int ng4[] = {6U, 0U};
static unsigned int ng5[] = {3U, 0U};
static unsigned int ng6[] = {11U, 0U};
static unsigned int ng7[] = {4U, 0U};
static unsigned int ng8[] = {7U, 0U};
static unsigned int ng9[] = {5U, 0U};
static unsigned int ng10[] = {9U, 0U};
static unsigned int ng11[] = {32U, 0U};
static unsigned int ng12[] = {34U, 0U};
static unsigned int ng13[] = {36U, 0U};
static unsigned int ng14[] = {37U, 0U};
static unsigned int ng15[] = {42U, 0U};
static unsigned int ng16[] = {39U, 0U};
static unsigned int ng17[] = {24U, 0U};
static unsigned int ng18[] = {27U, 0U};
static unsigned int ng19[] = {8U, 0U};
static int ng20[] = {0, 0};
static unsigned int ng21[] = {31U, 31U};



static void Always_26_0(char *t0)
{
    char t6[8];
    char t31[16];
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
    char *t28;
    char *t29;
    int t30;

LAB0:    t1 = (t0 + 2528U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(26, ng0);
    t2 = (t0 + 2848);
    *((int *)t2) = 1;
    t3 = (t0 + 2560);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(26, ng0);

LAB5:    xsi_set_current_line(27, ng0);
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

LAB11:    xsi_set_current_line(28, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng3)));
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
        goto LAB16;

LAB13:    if (t18 != 0)
        goto LAB15;

LAB14:    *((unsigned int *)t6) = 1;

LAB16:    t8 = (t6 + 4);
    t23 = *((unsigned int *)t8);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB17;

LAB18:    xsi_set_current_line(29, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng5)));
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
        goto LAB23;

LAB20:    if (t18 != 0)
        goto LAB22;

LAB21:    *((unsigned int *)t6) = 1;

LAB23:    t8 = (t6 + 4);
    t23 = *((unsigned int *)t8);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB24;

LAB25:    xsi_set_current_line(30, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng7)));
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
        goto LAB30;

LAB27:    if (t18 != 0)
        goto LAB29;

LAB28:    *((unsigned int *)t6) = 1;

LAB30:    t8 = (t6 + 4);
    t23 = *((unsigned int *)t8);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB31;

LAB32:    xsi_set_current_line(31, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng9)));
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
        goto LAB37;

LAB34:    if (t18 != 0)
        goto LAB36;

LAB35:    *((unsigned int *)t6) = 1;

LAB37:    t8 = (t6 + 4);
    t23 = *((unsigned int *)t8);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB38;

LAB39:    xsi_set_current_line(32, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng4)));
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
        goto LAB44;

LAB41:    if (t18 != 0)
        goto LAB43;

LAB42:    *((unsigned int *)t6) = 1;

LAB44:    t8 = (t6 + 4);
    t23 = *((unsigned int *)t8);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB45;

LAB46:    xsi_set_current_line(33, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng8)));
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
        goto LAB51;

LAB48:    if (t18 != 0)
        goto LAB50;

LAB49:    *((unsigned int *)t6) = 1;

LAB51:    t8 = (t6 + 4);
    t23 = *((unsigned int *)t8);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB52;

LAB53:    xsi_set_current_line(34, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng2)));
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
        goto LAB58;

LAB55:    if (t18 != 0)
        goto LAB57;

LAB56:    *((unsigned int *)t6) = 1;

LAB58:    t8 = (t6 + 4);
    t23 = *((unsigned int *)t8);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB59;

LAB60:    xsi_set_current_line(50, ng0);
    t2 = ((char*)((ng21)));
    t3 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 5, 0LL);

LAB61:
LAB54:
LAB47:
LAB40:
LAB33:
LAB26:
LAB19:
LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(27, ng0);
    t28 = ((char*)((ng2)));
    t29 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t29, t28, 0, 0, 5, 0LL);
    goto LAB12;

LAB15:    t7 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB16;

LAB17:    xsi_set_current_line(28, ng0);
    t21 = ((char*)((ng4)));
    t22 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t22, t21, 0, 0, 5, 0LL);
    goto LAB19;

LAB22:    t7 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB23;

LAB24:    xsi_set_current_line(29, ng0);
    t21 = ((char*)((ng6)));
    t22 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t22, t21, 0, 0, 5, 0LL);
    goto LAB26;

LAB29:    t7 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB30;

LAB31:    xsi_set_current_line(30, ng0);
    t21 = ((char*)((ng8)));
    t22 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t22, t21, 0, 0, 5, 0LL);
    goto LAB33;

LAB36:    t7 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB37;

LAB38:    xsi_set_current_line(31, ng0);
    t21 = ((char*)((ng7)));
    t22 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t22, t21, 0, 0, 5, 0LL);
    goto LAB40;

LAB43:    t7 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB44;

LAB45:    xsi_set_current_line(32, ng0);
    t21 = ((char*)((ng10)));
    t22 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t22, t21, 0, 0, 5, 0LL);
    goto LAB47;

LAB50:    t7 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB51;

LAB52:    xsi_set_current_line(33, ng0);
    t21 = ((char*)((ng3)));
    t22 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t22, t21, 0, 0, 5, 0LL);
    goto LAB54;

LAB57:    t7 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB58;

LAB59:    xsi_set_current_line(34, ng0);

LAB62:    xsi_set_current_line(35, ng0);
    t21 = (t0 + 1048U);
    t22 = *((char **)t21);

LAB63:    t21 = ((char*)((ng11)));
    t30 = xsi_vlog_unsigned_case_compare(t22, 6, t21, 6);
    if (t30 == 1)
        goto LAB64;

LAB65:    t2 = ((char*)((ng12)));
    t30 = xsi_vlog_unsigned_case_compare(t22, 6, t2, 6);
    if (t30 == 1)
        goto LAB66;

LAB67:    t2 = ((char*)((ng13)));
    t30 = xsi_vlog_unsigned_case_compare(t22, 6, t2, 6);
    if (t30 == 1)
        goto LAB68;

LAB69:    t2 = ((char*)((ng14)));
    t30 = xsi_vlog_unsigned_case_compare(t22, 6, t2, 6);
    if (t30 == 1)
        goto LAB70;

LAB71:    t2 = ((char*)((ng15)));
    t30 = xsi_vlog_unsigned_case_compare(t22, 6, t2, 6);
    if (t30 == 1)
        goto LAB72;

LAB73:    t2 = ((char*)((ng16)));
    t30 = xsi_vlog_unsigned_case_compare(t22, 6, t2, 6);
    if (t30 == 1)
        goto LAB74;

LAB75:    t2 = ((char*)((ng17)));
    t30 = xsi_vlog_unsigned_case_compare(t22, 6, t2, 6);
    if (t30 == 1)
        goto LAB76;

LAB77:    t2 = ((char*)((ng18)));
    t30 = xsi_vlog_unsigned_case_compare(t22, 6, t2, 6);
    if (t30 == 1)
        goto LAB78;

LAB79:    t2 = ((char*)((ng1)));
    t30 = xsi_vlog_unsigned_case_compare(t22, 6, t2, 6);
    if (t30 == 1)
        goto LAB80;

LAB81:    t2 = ((char*)((ng5)));
    t30 = xsi_vlog_unsigned_case_compare(t22, 6, t2, 6);
    if (t30 == 1)
        goto LAB82;

LAB83:
LAB85:
LAB84:    xsi_set_current_line(47, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng20)));
    xsi_vlogtype_concat(t31, 36, 36, 2U, t2, 32, t3, 4);
    t4 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t4, t31, 0, 0, 5, 0LL);

LAB86:    goto LAB61;

LAB64:    xsi_set_current_line(36, ng0);
    t28 = ((char*)((ng2)));
    t29 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t29, t28, 0, 0, 5, 0LL);
    goto LAB86;

LAB66:    xsi_set_current_line(37, ng0);
    t3 = ((char*)((ng4)));
    t4 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t4, t3, 0, 0, 5, 0LL);
    goto LAB86;

LAB68:    xsi_set_current_line(38, ng0);
    t3 = ((char*)((ng1)));
    t4 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t4, t3, 0, 0, 5, 0LL);
    goto LAB86;

LAB70:    xsi_set_current_line(39, ng0);
    t3 = ((char*)((ng3)));
    t4 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t4, t3, 0, 0, 5, 0LL);
    goto LAB86;

LAB72:    xsi_set_current_line(40, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t4, t3, 0, 0, 5, 0LL);
    goto LAB86;

LAB74:    xsi_set_current_line(41, ng0);
    t3 = ((char*)((ng5)));
    t4 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t4, t3, 0, 0, 5, 0LL);
    goto LAB86;

LAB76:    xsi_set_current_line(42, ng0);
    t3 = ((char*)((ng7)));
    t4 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t4, t3, 0, 0, 5, 0LL);
    goto LAB86;

LAB78:    xsi_set_current_line(43, ng0);
    t3 = ((char*)((ng10)));
    t4 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t4, t3, 0, 0, 5, 0LL);
    goto LAB86;

LAB80:    xsi_set_current_line(44, ng0);
    t3 = ((char*)((ng9)));
    t4 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t4, t3, 0, 0, 5, 0LL);
    goto LAB86;

LAB82:    xsi_set_current_line(45, ng0);
    t3 = ((char*)((ng19)));
    t4 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t4, t3, 0, 0, 5, 0LL);
    goto LAB86;

}


extern void work_m_00000000002470791600_4231019343_init()
{
	static char *pe[] = {(void *)Always_26_0};
	xsi_register_didat("work_m_00000000002470791600_4231019343", "isim/tb_SingleCycle_isim_beh.exe.sim/work/m_00000000002470791600_4231019343.didat");
	xsi_register_executes(pe);
}
