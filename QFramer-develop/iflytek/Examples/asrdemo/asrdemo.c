// asrdemo.c : Defines the entry point for the console application.
//
#include "stdlib.h"
#include "stdio.h"
#include <windows.h>
#include <conio.h>
#include <errno.h>

#include "../../include/qisr.h"
#include "../../include/msp_cmn.h"
#include "../../include/msp_errors.h"


#ifdef _WIN64
#pragma comment(lib,"../../lib/msc_x64.lib")//x64
#else
#pragma comment(lib,"../../lib/msc.lib")//x86
#endif

#define  BUFFER_NUM  4096 
#define MAX_KEYWORD_LEN 4096
char GrammarID[128];

const char*  get_audio_file(void)
{
	char key = 0;
	while(key != 27)//��Esc���˳�
	{
		system("cls");//����
		printf("��ѡ����Ƶ�ļ���\n");
		printf("1.�ƴ�Ѷ��\n");
		printf("2.����ɽ����\n");
		printf("3.��³ʯ��\n");
		printf("4.һ�����������߰˾�ʮ\n");
		printf("ע�⣺����������Ƶ������˵�����ģ�����չʾЧ����\n      �ؼ����б���û�е�������չʾ����û�˵�Ĵ��ﲻ���б��У���õ�ʲô�����\n");
		key = getchar();
		switch(key)
		{
		case '1':
			printf("1.�ƴ�Ѷ��\n");
			return "wav/iflytek01.wav";                               //iflytek01��Ӧ����Ƶ���ݡ��ƴ�Ѷ�ɡ�
		case '2':
			printf("2.����ɽ����\n");
			return "wav/iflytek02.wav";                               //iflytek02��Ӧ����Ƶ���ݡ�����ɽ������
		case '3':
			printf("3.��³ʯ��\n");
			return "wav/iflytek03.wav";                               //iflytek03��Ӧ����Ƶ���ݡ���³ʯ����
		case '4':
			printf("4.һ�����������߰˾�ʮ\n");
			return "wav/iflytek04.wav";                               //iflytek04��Ӧ����Ƶ����"һ�����������߰˾�ʮ"
		default:
			continue;
		}
	}
	exit(0);
	return NULL;
}

int get_grammar_id( int upload)
{
	int ret = MSP_SUCCESS;
	const char * sessionID = NULL;
	char UserData[MAX_KEYWORD_LEN];
	unsigned int len = 0;
	const char* testID = NULL;
	FILE *fp = NULL;
	memset(UserData, 0, MAX_KEYWORD_LEN);
	if (0 == upload)

	{
		strcpy(GrammarID, "e7eb1a443ee143d5e7ac52cb794810fe");
		//���ID�����ϴ�֮���¼�����ġ��﷨�ϴ�֮�����ñ����ڷ������ϣ����Բ�Ҫ�����ϴ�ͬ�����﷨
		return ret;
	}	
	//�����Ҫ�����ϴ��﷨���������upload��ΪTRUE���Ϳ�����������ϴ��﷨����
	fp = fopen("asr_keywords_utf8.txt", "rb");//�ؼ����б��ļ�������utf8��ʽ
	if (fp == NULL)
	{   
		ret = -1 ;
		printf("keyword file cannot open\n");
		return ret;
	}
	len = (unsigned int)fread(UserData, 1, MAX_KEYWORD_LEN, fp);
	UserData[len] = 0;
	fclose(fp);
    testID = MSPUploadData("userword", UserData, len, "dtt = userword, sub = asr", &ret);// sub �������裬���򷵻ؿմ�
	if(ret != MSP_SUCCESS)
	{
		printf("UploadData with errorCode: %d \n", ret);
		return ret;
	}
	memcpy((void*)GrammarID, testID, strlen(testID));
	printf("GrammarID: \"%s\" \n", GrammarID);//����õ�GrammarID�������Ļ��
	return ret;
}

int run_asr(const char* asrfile ,  const char* param)
{
	char rec_result[1024*4] = {0};
	const char *sessionID;
	FILE *f_pcm = NULL;
	char *pPCM = NULL;
	int lastAudio = 0 ;
	int audStat = MSP_AUDIO_SAMPLE_CONTINUE ;
	int epStatus = MSP_EP_LOOKING_FOR_SPEECH;
	int recStatus = MSP_REC_STATUS_SUCCESS ;
	long pcmCount = 0;
	long pcmSize = 0;
	int errCode = 0 ;
	sessionID = QISRSessionBegin(GrammarID, param, &errCode); //��ʼһ·�Ự
	f_pcm = fopen(asrfile, "rb");
	if (NULL != f_pcm) {
		fseek(f_pcm, 0, SEEK_END);
		pcmSize = ftell(f_pcm);
		fseek(f_pcm, 0, SEEK_SET);
		pPCM = (char *)malloc(pcmSize);
		fread((void *)pPCM, pcmSize, 1, f_pcm);
		fclose(f_pcm);
		f_pcm = NULL;
	}//��ȡ��Ƶ�ļ�
	while (1) {
		unsigned int len = 6400;
		int ret;

		if (pcmSize < 12800) {
			len = pcmSize;
			lastAudio = 1;
		}
		audStat = MSP_AUDIO_SAMPLE_CONTINUE;//�к����Ƶ
		if (pcmCount == 0)
			audStat = MSP_AUDIO_SAMPLE_FIRST;
		if (len<=0)
		{
			break;
		}
		printf("csid=%s,count=%d,aus=%d,",sessionID,pcmCount/len,audStat);
		ret = QISRAudioWrite(sessionID, (const void *)&pPCM[pcmCount], len, audStat, &epStatus, &recStatus);//д��Ƶ
		printf("eps=%d,rss=%d,ret=%d\n",epStatus,recStatus,errCode);
		if (ret != 0)
			break;
		pcmCount += (long)len;
		pcmSize -= (long)len;
		if (recStatus == MSP_REC_STATUS_SUCCESS) {
			const char *rslt = QISRGetResult(sessionID, &recStatus, 0, &errCode);
			if (NULL != rslt)
				strcat(rec_result,rslt);
		}
		if (epStatus == MSP_EP_AFTER_SPEECH)
			break;
		_sleep(150);//ģ����˵��ʱ���϶
	}
	QISRAudioWrite(sessionID, (const void *)NULL, 0, MSP_AUDIO_SAMPLE_LAST, &epStatus, &recStatus);
	free(pPCM);
	pPCM = NULL;
	while (recStatus != MSP_REC_STATUS_COMPLETE && 0 == errCode) {
		const char *rslt = QISRGetResult(sessionID, &recStatus, 0, &errCode);
		if (NULL != rslt)
		{
			strcat(rec_result,rslt);
		}
		_sleep(150);
	}
	QISRSessionEnd(sessionID, NULL);
	printf("=============================================================\n");
	printf("The result is: %s\n",rec_result);
	printf("=============================================================\n");
	return errCode ;
}

int main(int argc, char* argv[])
{
	const char* login_config = "appid = 53d11199, work_dir =   .  ";//��¼����
	const char* param = "sub=asr,aue=speex-wb,auf=audio/L16;rate=16000,ent=sms16k"; //ע��sub=asr
	int ret = 0 ;
	char key = 0 ;
	int grammar_flag = 0 ;//0:���ϴ��ʱ�1���ϴ��ʱ�
	const char* asrfile = get_audio_file();//ѡ���ʶ��������ļ�
	ret = MSPLogin(NULL, NULL, login_config);//��һ������Ϊ�û������ڶ�������Ϊ���룬�����������ǵ�¼�������û�����������Ҫ��http://open.voicecloud.cnע�Ტ��ȡappid
	if ( ret != MSP_SUCCESS )
	{
		printf("MSPLogin failed , Error code %d.\n",ret);
		goto exit ;
	}
	memset(GrammarID, 0, sizeof(GrammarID));
	ret = get_grammar_id(grammar_flag);
	if(ret != MSP_SUCCESS)
	{
		printf("get_grammar_id with errorCode: %d \n", ret);
		goto exit ;
	}
 	ret = run_asr(asrfile, param);
	if(ret != MSP_SUCCESS)
	{
		printf("run_asr with errorCode: %d \n", ret);
		goto exit;
	}
	exit:
	MSPLogout();//�˳���¼
	key = _getch();
	return 0;
}

