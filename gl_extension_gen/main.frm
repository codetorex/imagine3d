VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form main 
   Caption         =   "CodeGen"
   ClientHeight    =   5730
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6375
   Icon            =   "main.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5730
   ScaleWidth      =   6375
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton Command2 
      Caption         =   "Extension List"
      Height          =   615
      Left            =   1320
      TabIndex        =   0
      Top             =   120
      Width           =   1695
   End
   Begin MSComDlg.CommonDialog cd 
      Left            =   240
      Top             =   1080
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
End
Attribute VB_Name = "main"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
cd.Filter = "Text File(*.txt)|*.TXT"
cd.ShowOpen
If cd.FileName <> "" Then
    fops.gen_extension cd.FileName
End If
End Sub

Private Sub Command2_Click()
fops.gen_list "vertex program.txt", "vertex program2.txt"
End Sub

