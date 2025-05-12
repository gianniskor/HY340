// #include "funcLib.h"

// bool validNumberExpr(expr *e){
//     switch (e->type)
//     {
//     case var_e:
//     case tableitem_e:
//     case arithexpr_e:
//     case assignexpr_e:
//     case constint_e:
//     case constdouble_e:
//         return true;
//         /*break;*/
//     default:
//         printf("Invalid arithmetic op, at %d -> line\n");
//         return false;
//         /*break;*/
//     }
// }

// bool tmpCheck(expr* e){
//     const string str = "";
//     const string symName = e->sym->getName();
//     if( e->sym!=NULL && (e->sym->type == LOCAL_VAR || e->sym->type == GLOBAL_VAR) && !symName.empty() &&symName.front() == '_'){
//         return true;
//     }
//     return false;
// }

// expr* evaluateNumber(expr* e, expr* e2, iopcode opcode){
//     bool flag1, flag2;
//     flag1 = validNumberExpr(e);
//     flag2 = validNumberExpr(e2);
//     Symbol *tmp;
//     expr* tmpExpr;
//     if(flag1 == false || flag2 == false){
//         printf("Error, flag in eNum is false \n");
//         exit(-1);
//     }
//     if(tmpCheck(e) == true){
//         tmp = e->sym;
//         tmpExpr = symToExpr(tmp);
//     }else if(tmpCheck(e2) == true){
//         tmp = e2->sym;
//         tmpExpr = symToExpr(tmp);
//     }else{
//         tmpExpr = newTempExpr();
//     }
//     if(opcode != sub || opcode != add || opcode != div_op || opcode != mul || opcode != mod){
//         cerr << "invalid opcode ,in function evaluateNumber" << endl;
//     }else{
//         emit(opcode,e,e2,tmpExpr);
//     }
//     return tmpExpr;
// }
