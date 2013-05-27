#include "instruction.h"
#include "argument.h"
#include "variable.h"

bool cbBadCmd(const char* cmd)
{
    unsigned int value=0;
    int valsize=0;
    bool isvar=false;
    if(getvaluefromstring(cmd, &value, &valsize, 0, &isvar)) //dump variable/value/register/etc
    {
        //printf("[DEBUG] valsize: %d\n", valsize);
        if(valsize)
            valsize*=2;
        else
            valsize=1;
        char format_str[deflen]="";
        if(isvar)// and *cmd!='.' and *cmd!='x') //prevent stupid 0=0 stuff
        {
            if(value>15)
            {
                sprintf(format_str, "%%s=%%.%dX (%%ud)\n", valsize);
                printf(format_str, cmd, value, value);
            }
            else
            {
                sprintf(format_str, "%%s=%%.%dX\n", valsize);
                printf(format_str, cmd, value);
            }
        }
        else
        {
            if(value>15)
            {
                sprintf(format_str, "%%.%dX (%%ud)\n", valsize);
                printf(format_str, value, value);
            }
            else
            {
                sprintf(format_str, "%%.%dX\n", valsize);
                printf(format_str, value);
            }
        }
    }
    else //unknown command
    {
        char cmd_[deflen]="";
        strcpy(cmd_, cmd);
        int len=strlen(cmd_);
        for(int i=0; i<len; i++)
        {
            if(cmd_[i]==' ')
            {
                cmd_[i]=0;
                break;
            }
        }
        if(*cmd_=='$')
            printf("unknown variable: \"%s\"\n", cmd_);
        else
            printf("unknown command: \"%s\"\n", cmd_);
    }
    return true;
}

bool cbInstrVar(const char* cmd)
{
    char arg1[deflen]="";
    char arg2[deflen]="";
    if(!argget(cmd, arg1, 0, false)) //var name
        return true;
    argget(cmd, arg2, 1, true); //var value (optional)
    unsigned int value=0;
    if(!getvaluefromstring(arg2, &value, 0, 0, 0))
    {
        printf("invalid value \"%s\"\n", arg2);
        return true;
    }
    if(!varnew(arg1, (void*)value, VAR_USER))
        printf("error creating variable \"%s\"\n", arg1);
    else
    {
        if(value>15)
            printf("%s=%X (%ud)\n", arg1, value, value);
        else
            printf("%s=%X\n", arg1, value);
    }
    return true;
}

bool cbInstrVarDel(const char* cmd)
{
    char arg1[deflen]="";
    if(!argget(cmd, arg1, 0, false)) //var name
        return true;
    if(!vardel(arg1, false))
        printf("could not delete variable \"%s\"\n", arg1);
    else
        printf("deleted variable \"%s\"\n", arg1);
    return true;
}

bool cbInstrMov(const char* cmd)
{
    char arg1[deflen]="";
    char arg2[deflen]="";
    if(!argget(cmd, arg1, 0, false)) //dest name
        return true;
    if(!argget(cmd, arg2, 1, false)) //src name
        return true;
    unsigned int set_value=0;
    if(!getvaluefromstring(arg2, &set_value, 0, 0, 0))
    {
        printf("invalid src \"%s\"\n", arg2);
        return true;
    }
    if(!varset(arg1, (void*)set_value, false))
    {
        if(*arg1!='$')
        {
            printf("invalid dest \"%s\"\n", arg1);
            return true;
        }
        varnew(arg1, (void*)set_value, VAR_USER);
    }
    unsigned int value=0;
    varget(arg1, &value, 0, 0);
    if(value>15)
        printf("%s=%X (%ud)\n", arg1, value, value);
    else
        printf("%s=%X\n", arg1, value);
    return true;
}

bool cbInstrVarList(const char* cmd)
{
    dbg("varlist");
    char arg1[deflen]="";
    argget(cmd, arg1, 0, true);
    int filter=0;
    if(!strcasecmp(arg1, "USER"))
        filter=VAR_USER;
    else if(!strcasecmp(arg1, "READONLY"))
        filter=VAR_READONLY;
    else if(!strcasecmp(arg1, "SYSTEM"))
        filter=VAR_SYSTEM;
    VAR* cur=vargetptr();
    if(!cur)
    {
        puts("no variables");
        return true;
    }
    unsigned int value=0;
    bool bNext=true;
    while(bNext)
    {
        if(cur->name)
        {
            char name[deflen]="";
            strcpy(name, cur->name);
            int len=strlen(name);
            for(int i=0; i<len; i++)
                if(name[i]==1)
                    name[i]='/';
            value=(unsigned int)cur->value.value;
            if(filter)
            {
                if(cur->type==filter)
                {
                    if(value>15)
                        printf("%s=%X (%ud)\n", name, value, value);
                    else
                        printf("%s=%X\n", name, value);
                }
            }
            else
            {
                if(value>15)
                    printf("%s=%X (%ud)\n", name, value, value);
                else
                    printf("%s=%X\n", name, value);
            }
        }
        cur=cur->next;
        if(!cur)
            bNext=false;
    }
    return true;
}