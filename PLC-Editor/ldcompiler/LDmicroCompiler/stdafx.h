// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//

#pragma once

#include <stddef.h>
#include <stdio.h>


using namespace System;

bool IsNumber(String^ str);
String^ BoolToString(bool value, String^ ifTrue, String^ ifFalse);
String^ RemoveDollar(String^ str);

int IndexOfClosingParenthesis(String^ str);

// TODO�: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme
