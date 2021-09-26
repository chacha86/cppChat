#include <sstream>
#include "MyChat.h"
#define ENTER 13
#define BACKSPACE 8

using namespace MyChat;
using namespace std;

ChatController::ChatController() {
	memset(this->msgBuffer, 0, sizeof(msgBuffer));
	this->msgBufferIndex = 0;
	this->recvFlag = 0;
	chatView.paintChatDisplay(msgList);
}

void ChatController::run(string user) {
	while (true) {
		if (recvFlag == 1) { // �������� �޽����� ���� ��,
			repaintWhenRecvFromServer();
		}
		if (kbhit()) { // Ű���尡 �Էµ��� ��
			char key = getch(); // Ű���� ��������

			if (key == ENTER) { // ���Ͷ��
				sendToServer(user);
			}
			else if (key == BACKSPACE) {

			}
			else {
				msgBuffer[msgBufferIndex++] = key;
				cout << key;
			}
		}
	}
}

void ChatController::repaintWhenRecvFromServer() {
	// ä�� �޽��� ����
	msgList.push_back("�������� �޽����� ��..");

	// ä��â �ٽ� �׸���
	chatView.paintChatDisplay(msgList);

	// �Է����̴� ä�� �޽����� �ٽ� �׷���
	for (int i = 0; i < msgBufferIndex; i++) {
		cout << msgBuffer[i];
	}

	// �Է� Ŀ���� index ��ġ�� �ٲ�
	chatView.moveToChatInputPosX(msgBufferIndex);

	// ���� ���·� �ٲ�
	recvFlag = 0;
}

string ChatController::convertChatDataToString(string user, const char* msg) {
	string rsMsg;
	rsMsg = rsMsg.append(user);
	rsMsg = rsMsg.append(":");
	rsMsg = rsMsg.append(msg);
	rsMsg = rsMsg.append("\n");

	return msg;
}

ChatData ChatController::convertStringToChatData(string msg) {
	ChatData chatData;

	vector<string> answer;
	stringstream ss(msg);
	string temp;

	while (getline(ss, temp, ':')) {
		answer.push_back(temp);
	}
	
	chatData.userId = answer[0];
	chatData.msg = answer[1].c_str();

	return chatData;
}

int ChatController::joinServer(string ip, int port) {
	if (chatSocket == NULL) {
		chatSocket = new MySocket::Socket(ip.c_str(), port);
		return 0;
	}
	else {
		return -1;
	}
}

void ChatController::sendToServer(string user) {
	// �޽��� ������
	memset(msgBuffer, 0, sizeof(msgBuffer)); // msgBuffer�� ���� ����.
	string sendMsg = convertChatDataToString(user, msgBuffer);

	// �޽����� �������Ƿ� ä��â �ٽ� �׸���
	chatSocket->send_data(sendMsg.c_str());

	chatView.paintChatDisplay(msgList);
	// �޽����� �������Ƿ� �޽��� ���� index�ʱ�ȭ, Ŀ���� ��ġ �ʱ�ȭ
	msgBufferIndex = 0;
	chatView.instantiateChatInputPos();

}

void ChatController::setRecvFlag(int recvFlag) {
	this->recvFlag = recvFlag;
}