class CEventManager
{
public:

	static CEventManager* getInstance();

private:

	CEventManager();
	static CEventManager* m_pInstance;
};