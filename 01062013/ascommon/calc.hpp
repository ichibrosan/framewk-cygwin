// $Log: calc.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_calculat[] = "$Id: calc.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"CALC8")) {
  fprintf(g_flog,"Processing CALC8 directive\n");
  g_iErrorNo ^= ERROR_UNKOP;
  g_iLineType = TYPE_DIR;
  if(0 != strlen(g_szParms)) {
    char myszTerm1[DEFAULT_STRSIZE];
    char myszTerm2[DEFAULT_STRSIZE];
    char szOp[DEFAULT_STRSIZE];
    unsigned char acc;
    calc(g_szParms,myszTerm1,szOp,myszTerm2);
        unsigned char term1 = resolvep8(myszTerm1);
        unsigned char term2 = resolvep8(myszTerm2);
    switch(szOp[0]) {
        case '+': acc = term1 + term2; break;
        case '-': acc = term1 - term2; break;
        case '*': acc = term1 * term2; break;
        case '/': acc = term1 / term2; break;
        case '|': acc = term1 | term2; break;
	default:  g_iErrorNo |= ERROR_OPERATOR;
    };
    g_pCSymbols->add(g_szLabel,TYPE_U8,(unsigned char)acc);
  }
}

if(0 == strcmp(strupr(g_szOpcode),"CALC16")) {
  fprintf(g_flog,"Processing CALC16 directive\n");
  g_iErrorNo ^= ERROR_UNKOP;
  g_iLineType = TYPE_DIR;
  if(0 != strlen(g_szParms)) {
    char myszTerm1[DEFAULT_STRSIZE];
    char myszTerm2[DEFAULT_STRSIZE];
    char szOp[DEFAULT_STRSIZE];
    unsigned int acc;
    calc(g_szParms,myszTerm1,szOp,myszTerm2);
    unsigned int term1 = resolvep16(myszTerm1);
    fprintf(g_flog,"term1 is 0x%04X\n",term1);
    unsigned int term2 = resolvep16(myszTerm2);
    fprintf(g_flog,"term2 is 0x%04X\n",term2);
    switch(szOp[0]) {
        case '+': acc = term1 + term2; break;
        case '-': acc = term1 - term2; break;
        case '*': acc = term1 * term2; break;
        case '/': acc = term1 / term2; break;
        case '&': acc = term1 & term2; break;
        case '|': acc = term1 | term2; break;
        default: g_iErrorNo |= ERROR_OPERATOR;
    };
    fprintf(g_flog,"acc is 0x%04X\n",acc);
    g_pCSymbols->add(g_szLabel,TYPE_U16,(unsigned int)acc);
  }
}

if(0 == strcmp(strupr(g_szOpcode),"CALC32")) {
  fprintf(g_flog,"Processing CALC32 directive\n");
  g_iErrorNo ^= ERROR_UNKOP;
  g_iLineType = TYPE_DIR;
  if(0 != strlen(g_szParms)) {
    char myszTerm1[DEFAULT_STRSIZE];
    char myszTerm2[DEFAULT_STRSIZE];
    char szOp[DEFAULT_STRSIZE];
    unsigned long acc;
    calc(g_szParms,myszTerm1,szOp,myszTerm2);
    unsigned long term1 = resolvep32(myszTerm1);
    unsigned long term2 = resolvep32(myszTerm2);
    switch(szOp[0]) {
        case '+': acc = term1 + term2; break;
        case '-': acc = term1 - term2; break;
        case '*': acc = term1 * term2; break;
        case '/': acc = term1 / term2; break;
        case '&': acc = term1 & term2; break;
        case '|': acc = term1 | term2; break;
	default: g_iErrorNo |= ERROR_OPERATOR;
    };
    g_pCSymbols->add(g_szLabel,TYPE_U32,(unsigned long)acc);
  }
}

if(0 == strcmp(strupr(g_szOpcode),"CALC64")) {
  fprintf(g_flog,"Processing CALC64 directive\n");
  g_iErrorNo ^= ERROR_UNKOP;
  g_iLineType = TYPE_DIR;
  if(0 != strlen(g_szParms)) {
    char myszTerm1[DEFAULT_STRSIZE];
    char myszTerm2[DEFAULT_STRSIZE];
    char szOp[DEFAULT_STRSIZE];
    unsigned long long acc;
    calc(g_szParms,myszTerm1,szOp,myszTerm2);
    unsigned long long term1 = resolvep64(myszTerm1);
    unsigned long long term2 = resolvep64(myszTerm2);
    switch(szOp[0]) {
        case '+': acc = term1 + term2; break;
        case '-': acc = term1 - term2; break;
        case '*': acc = term1 * term2; break;
        case '/': acc = term1 / term2; break;
        case '&': acc = term1 & term2; break;
        case '|': acc = term1 | term2; break;
	default: g_iErrorNo |= ERROR_OPERATOR; break;
    };
    g_pCSymbols->add(g_szLabel,TYPE_U64,(unsigned long long)acc);
  }
}

////////////////////
// eof - calc.hpp //
////////////////////
