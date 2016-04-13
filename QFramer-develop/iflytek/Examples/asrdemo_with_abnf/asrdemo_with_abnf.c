// asrdemo_with_abnf.c : Defines the entry point for the console application.
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
		printf("1.055165309093\n");
		printf("2.18012345678\n");
		printf("3.�ʱ�230088\n");
		printf("4.���տƴ�Ѷ����Ϣ�Ƽ��ɷ����޹�˾\n");
		printf("ע�⣺����������Ƶ�����ֺ����ֵĻ�ϣ����ֲ���Ҳ�ھ����ܵ������ֿ������Ŷȵ͡�\n      ������û�����֣�����Ϊ��������\n");
		key = getchar();
		switch(key)
		{
		case '1':
			printf("1.055165309093\n");
			return "wav/iflytek05.wav";                                   //iflytek05��Ӧ����Ƶ���ݡ�055165309093��
		case '2':
			printf("2.18012345678\n");
			return "wav/iflytek06.wav";                                   //iflytek06��Ӧ����Ƶ���ݡ�1890123456789��
		case '3':
			printf("3.�ʱ�230088\n");
			return "wav/iflytek07.wav";                                   //iflytek07��Ӧ����Ƶ���ݡ��ʱ�230008��
		case '4':
			printf("4.���տƴ�Ѷ����Ϣ�Ƽ��ɷ����޹�˾\n");
			return "wav/iflytek08.wav";                                   //iflytek08��Ӧ����Ƶ���ݡ����տƴ�Ѷ����Ϣ�Ƽ��ɷ����޹�˾��
		default:
			continue;
		}
	}
	exit(0);
	return NULL;
}

const char* get_grammar( const char* filename )
{
	int ret = MSP_SUCCESS;
	int file_len = 0;
	char* grammar = NULL;
	FILE *fp=NULL; 
	fp=fopen(filename,"rb");
	if (NULL == fp)
	{
		printf("get_grammar| open file \"%s\" failed.\n",filename ? filename : "");
		return NULL;
	}
	fseek(fp,0L,SEEK_END);
	file_len=ftell(fp);
	fseek(fp,0L,SEEK_SET);

	grammar = (char*)malloc(file_len+1); //���ļ��ж�ȡ�﷨��ע���ı�����ΪGB2312
	fread((void*)grammar,1,file_len,fp);
	grammar[file_len]='\0'; //�ַ�����β
	fclose(fp);
	return grammar;
}

void release_grammar(const char** grammar)
{
	if (*grammar)
	{
		free((void*)*grammar);
		*grammar = NULL;
	}	
}

int run_asr(const char* asrfile ,  const char* param , const char* grammar)
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
	int errCode = 10 ;
	sessionID = QISRSessionBegin(NULL, param, &errCode); //asr
	QISRGrammarActivate(sessionID, grammar, NULL, 0);//����ѡ����QISRSessionBegin��һ����������grammar�����ͨ��QISRGrammarActivate�����﷨�����Զ�ε���QISRGrammarActivate���������﷨��
	f_pcm = fopen(asrfile, "rb");
	if (NULL != f_pcm) {
		fseek(f_pcm, 0, SEEK_END);
		pcmSize = ftell(f_pcm);
		fseek(f_pcm, 0, SEEK_SET);
		pPCM = (char *)malloc(pcmSize);
		fread((void *)pPCM, pcmSize, 1, f_pcm);
		fclose(f_pcm);
		f_pcm = NULL;
	}
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
	while (recStatus != MSP_REC_STATUS_COMPLETE && errCode == 0) {
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
	return errCode;
}

int main(int argc, char* argv[])
{
	const char* login_config = "appid = 53d11199, work_dir =   .  ";//��¼����
	const char* param = "sub=asr,ssm=1,aue=speex-wb,auf=audio/L16;rate=16000,ent=sms16k";//ע��sub=asr
	const char* grammar = NULL;
	int ret = 0 ;
	char key = 0 ;
	const char* asrfile = get_audio_file();//ѡ���ʶ��������ļ�
	ret = MSPLogin(NULL, NULL, login_config);//��һ������Ϊ�û������ڶ�������Ϊ���룬�����������ǵ�¼�������û�����������Ҫ��http://open.voicecloud.cnע�Ტ��ȡappid
	if ( ret != MSP_SUCCESS )
	{
		printf("MSPLogin failed , Error code %d.\n",ret);
		goto exit ;
	}
	grammar = get_grammar( "gm_continuous_digit.abnf" );//��ȡ�﷨�ļ�
	ret = run_asr(asrfile, param, grammar);
	if(ret != MSP_SUCCESS)
	{
		printf("run_asr with errorCode: %d \n", ret);
		goto error ;
	}
	error:
	release_grammar(&grammar);
	exit:
	MSPLogout();
	key = _getch();
	return 0;
}

