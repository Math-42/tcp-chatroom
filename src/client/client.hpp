

class Client
{
private:
	int port;
	int maxMessageSize;

protected:
	virtual void onReceive();

public:
	Client(int port, int maxMessage);
	void send();
	void connect();
};