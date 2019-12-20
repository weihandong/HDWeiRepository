#ifndef _EXEC_INSTRUCTION_H
#define _EXEC_INSTRUCTION_H

class CPTZ;
class CUartDev;
class CExecAction;

/* 操作命令结构体(用于SDK)
 *
 */
typedef struct {
    char *name;
	int cmd_no;
    void (CExecAction::*func)(char *arg);
}command_t;

/* 操作指令结构体(用于RS485)
 *
 */
typedef struct {
	const char *name;
	const int instruction_no;
 	const unsigned char pelco_d[7];
}instruction_t;

class CExecAction
{
public:
	CExecAction();
	~CExecAction();

	void uartCom_Init();
	int Exec_Command(const char *str_cmd, char *data);
	int Exec_Instruction(char *instruct, char *value);
	int Exec_Instruction(int instruct, char *value);

    void Login_Equipment(char *arg);
    void Logout_Equipment(char *arg);
private:
	int m_Errorno;
	int m_UserID;
	CUartDev *pUartDev;
	CPTZ *pPtz;
	
protected:
	void set_Errorno(void);
	int get_Errorno(void);
};



#endif
















