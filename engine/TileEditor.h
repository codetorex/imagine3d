
namespace TileEditor
{
	GWindow MainWindow;
	GTextbox MinSize;
	GTextbox Area;
	GButton Allc;



	void InitTileEditor()
	{
		MainWindow.caption="Tile Editor v0.3b";
		Allc.caption = "Allocate";
		CHandle(&MainWindow.ghand,10,10,500,500,true,0);
		CHandle(&MinSize.ghand,4,20,25,15,true,&MainWindow.ghand);
		CHandle(&Area.ghand,30,20,25,15,true,&MainWindow.ghand);
		CHandle(&Allc.ghand,4,40,50,15,true,&MainWindow.ghand);
	}

	void RunTileEditor()
	{
		MainWindow.render();
		MinSize.render();
		Area.render();
		Allc.render();
	}
}