Attribute VB_Name = "fops"
Sub gen_extension(fname As String)
Dim l As String
Open fname For Input As #1
Open "export.txt" For Output As #2
    Do While Not EOF(1)
        Line Input #1, l
        a = InStr(1, l, " ") - 1 ' ilk boslugu bul
        pname = Mid(l, 1, a) ' pointer ismi
        b = InStr(a, l, vbTab) 'tab bul
        func = Mid(l, a + 2, b - a - 1)
        RTrim (LTrim(Trim(func)))
        func = trimtab(func)
        sonuc = func & " = (" & pname & ")wglGetProcAddress(""" & func & """);"
        Print #2, sonuc
    Loop
Close #1
Close #2
End Sub

Sub gen_list(fname As String, fname2 As String)
Dim l As String
Dim l2 As String
Open fname For Input As #1
Open fname2 For Input As #3
Open "export2.txt" For Output As #2
Open "export3.txt" For Output As #4
    Do While Not EOF(1)
        Line Input #1, l
        Line Input #3, l2
        a = InStr(1, l, "APIENTRYP") + 10
        pname = Mid(l, a, InStr(a, l, ")") - a)
        
        a = InStr(1, l2, "APIENTRY") + 9
        pname2 = Mid(l2, a, InStr(a, l2, "(") - a - 1)
        
        sonuc = "extern " & pname & " " & pname2 & ";"
        Print #2, sonuc
    
        Print #4, pname2 & " = (" & pname & ")wglGetProcAddress(""" & pname2 & """);"
    Loop
Close #1
Close #3
Close #2
Close #4
End Sub


Function trimtab(ByVal what As String) As String
    Dim temp As String
    For i = 1 To Len(what)
        If (Mid(what, i, 1) = vbTab) Or (Mid(what, i, 1) = " ") Then
            
        Else
            temp = temp & Mid(what, i, 1)
        End If
    Next
    trimtab = temp
End Function
