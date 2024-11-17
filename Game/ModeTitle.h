//----------------------------------------------------------------------
// @filename ModeTitle.h
// @author: Fukuma Kyohei
// @explanation
// タイトル画像を描画するモード
//----------------------------------------------------------------------
class ModeTitle : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	//画像
	int _cg;
};

