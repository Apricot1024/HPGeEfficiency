#include <TFile.h>
#include <TH1.h>

void hisaddlyj() {
    // 打开三个包含直方图的ROOT文件
    TFile *file1 = TFile::Open("56AnaEx01.root");
    TFile *file2 = TFile::Open("147AnaEx01.root");
    // TFile *file3 = TFile::Open("58AnaEx01.root");

    // 从每个文件中读取名为"h"的直方图
    TH1F *hist1 = (TH1F*)file1->Get("h");
    TH1F *hist2 = (TH1F*)file2->Get("h");
    // TH1F *hist3 = (TH1F*)file3->Get("h");

    // 创建一个新的直方图来存储相加的结果，使用第一个直方图作为模板
    TH1F *histSum = (TH1F*)hist1->Clone("histSum");
    histSum->Reset(); // 重置直方图，确保从空直方图开始相加

    // 将三个直方图相加
    histSum->Add(hist1);
    histSum->Add(hist2);
    // histSum->Add(hist3);

    // 创建一个新的ROOT文件来存储相加后的直方图
    TFile *newFile = new TFile("AnaEx01.root", "RECREATE");
    histSum->Write(); // 将相加后的直方图写入新文件

    // 关闭所有打开的文件
    file1->Close();
    file2->Close();
    // file3->Close();
    newFile->Close();
}