/* Classic Ladder Project */
/* Copyright (C) 2001-2015 Marc Le Douarain */
/* http://www.sourceforge.net/projects/classicladder */
/* http://sites.google.com/site/classicladder */
/* October 2007 */
/* ------------------------ */
/* Variable base names list */
/* ------------------------ */
/* This library is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU Lesser General Public */
/* License as published by the Free Software Foundation; either */
/* version 2.1 of the License, or (at your option) any later version. */

/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU */
/* Lesser General Public License for more details. */

/* You should have received a copy of the GNU Lesser General Public */
/* License along with this library; if not, write to the Free Software */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */



typedef struct StrConvIdVarName
{
	char * StringBaseVarName;
	int iTypeVar;
	int iIdVar;
	/* differents depths sizes */
	int iSize1;			/* for depth 1 */
	int iSize2;			/* pour profondeur 2 */
	int iSize3;			/* pour profondeur 3 */
	/* offset 0 or 1 first value for each depth */
	int iFirstVal1;
	int iFirstVal2;
	int iFirstVal3;
	char cReadWriteAccess;
}StrConvIdVarName;

// Table of the defaults names variables (without the the first '%'' character)
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!! When adding something here, do not forget function UpdateSizesOfConvVarNameTable() below !!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
StrConvIdVarName TableConvIdVarName[] = {
		{ "B%d", VAR_MEM_BIT, 0, /*sizes*/ NBR_BITS_DEF, -1, -1, /*offsets */ 0, 0, 0, TRUE },
#ifdef OLD_TIMERS_MONOS_SUPPORT
		{ "T%d.D", VAR_TIMER_DONE, 0, /*sizes*/ NBR_TIMERS_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "T%d.R", VAR_TIMER_RUNNING, 0, /*sizes*/ NBR_TIMERS_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "T%d.P", VAR_TIMER_PRESET, 0, /*sizes*/ NBR_TIMERS_DEF, -1, -1, /*offsets */ 0, 0, 0, TRUE },
		{ "T%d.V", VAR_TIMER_VALUE, 0, /*sizes*/ NBR_TIMERS_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		
		{ "M%d.R", VAR_MONOSTABLE_RUNNING, 0, /*sizes*/ NBR_MONOSTABLES_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "M%d.P", VAR_MONOSTABLE_PRESET, 0, /*sizes*/ NBR_MONOSTABLES_DEF, -1, -1, /*offsets */ 0, 0, 0, TRUE },
		{ "M%d.V", VAR_MONOSTABLE_VALUE, 0, /*sizes*/ NBR_MONOSTABLES_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
#endif
		{ "C%d.D", VAR_COUNTER_DONE, 0, /*sizes*/ NBR_COUNTERS_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "C%d.E", VAR_COUNTER_EMPTY, 0, /*sizes*/ NBR_COUNTERS_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "C%d.F", VAR_COUNTER_FULL, 0, /*sizes*/ NBR_COUNTERS_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "C%d.P", VAR_COUNTER_PRESET, 0, /*sizes*/ NBR_COUNTERS_DEF, -1, -1, /*offsets */ 0, 0, 0, TRUE },
		{ "C%d.V", VAR_COUNTER_VALUE, 0, /*sizes*/ NBR_COUNTERS_DEF, -1, -1, /*offsets */ 0, 0, 0, TRUE /*FALSE*/ },
		
		{ "TM%d.Q", VAR_TIMER_IEC_DONE, 0, /*sizes*/ NBR_TIMERS_IEC_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "TM%d.P", VAR_TIMER_IEC_PRESET, 0, /*sizes*/ NBR_TIMERS_IEC_DEF, -1, -1, /*offsets */ 0, 0, 0, TRUE },
		{ "TM%d.V", VAR_TIMER_IEC_VALUE, 0, /*sizes*/ NBR_TIMERS_IEC_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		
		{ "R%d.E", VAR_REGISTER_EMPTY, 0, /*sizes*/ NBR_REGISTERS_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "R%d.F", VAR_REGISTER_FULL, 0, /*sizes*/ NBR_REGISTERS_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "R%d.I", VAR_REGISTER_IN_VALUE, 0, /*sizes*/ NBR_REGISTERS_DEF, -1, -1, /*offsets */ 0, 0, 0, TRUE },
		{ "R%d.O", VAR_REGISTER_OUT_VALUE, 0, /*sizes*/ NBR_REGISTERS_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "R%d.S", VAR_REGISTER_NBR_VALUES, 0, /*sizes*/ NBR_REGISTERS_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		
		{ "I%d", VAR_PHYS_INPUT, 0, /*sizes*/ NBR_PHYS_INPUTS_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "Q%d", VAR_PHYS_OUTPUT, 0, /*sizes*/ NBR_PHYS_OUTPUTS_DEF, -1, -1, /*offsets */ 0, 0, 0, TRUE },
		
		{ "QLED%d", VAR_USER_LED, 0, /*sizes*/ NBR_USERS_LEDS, -1, -1, /*offsets */ 0, 0, 0, TRUE },
		{ "W%d", VAR_MEM_WORD, 0, /*sizes*/ NBR_WORDS_DEF, -1, -1, /*offsets */ 0, 0, 0, TRUE },
#ifdef SEQUENTIAL_SUPPORT
		{ "X%d.A", VAR_STEP_ACTIVITY, 0, /*sizes*/ NBR_STEPS, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "X%d.V", VAR_STEP_TIME, 0, /*sizes*/ NBR_STEPS, -1, -1, /*offsets */ 0, 0, 0, FALSE },
#endif
		{ "IW%d", VAR_PHYS_WORD_INPUT, 0, /*sizes*/ NBR_PHYS_WORDS_INPUTS_DEF, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "QW%d", VAR_PHYS_WORD_OUTPUT, 0, /*sizes*/ NBR_PHYS_WORDS_OUTPUTS_DEF, -1, -1, /*offsets */ 0, 0, 0, TRUE },
		
		{ "S%d", VAR_SYSTEM, 0, /*sizes*/ NBR_VARS_SYSTEM, -1, -1, /*offsets */ 0, 0, 0, FALSE },
		{ "SW%d", VAR_WORD_SYSTEM, 0, /*sizes*/ NBR_VARS_WORDS_SYSTEM, -1, -1, /*offsets */ 0, 0, 0, FALSE },

		{ NULL, 0, 0, /*sizes*/ 0, 0, 0, /*offsets */ 0, 0, 0, FALSE }  //END
};

// use the real allocated sizes in the table now
// can not be done before in the table, because they aren't constants !!!
void UpdateSizesOfConvVarNameTable( void )
{
	int ScanTable = 0;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_BITS;
#ifdef OLD_TIMERS_MONOS_SUPPORT
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_TIMERS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_TIMERS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_TIMERS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_TIMERS;
	
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_MONOSTABLES;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_MONOSTABLES;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_MONOSTABLES;
#endif
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_COUNTERS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_COUNTERS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_COUNTERS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_COUNTERS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_COUNTERS;
	
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_TIMERS_IEC;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_TIMERS_IEC;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_TIMERS_IEC;
	
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_REGISTERS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_REGISTERS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_REGISTERS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_REGISTERS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_REGISTERS;
	
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_PHYS_INPUTS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_PHYS_OUTPUTS;
	
	ScanTable++; // Nothing here (NBR_USERS_LEDS=constant!)
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_WORDS;
#ifdef SEQUENTIAL_SUPPORT
	ScanTable++; // Nothing here (NBR_STEPS=constant!)
	ScanTable++; // Nothing here (NBR_STEPS=constant!)
#endif
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_PHYS_WORDS_INPUTS;
	TableConvIdVarName[ ScanTable++ ].iSize1 = NBR_PHYS_WORDS_OUTPUTS;

	ScanTable++; // Nothing here (NBR_VARS_SYSTEM=constant!)
	ScanTable++; // Nothing here (NBR_VARS_WORDS_SYSTEM=constant!)
}

