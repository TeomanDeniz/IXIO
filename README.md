# IXIO
Create, edit or delete pages in ix.io
### [DOWNLOAD](http://maximum-tension.com/)
```
IXIO.exe {COMMAND} "{INPUT}" "{USERNAME}" "{PASSWORD}" "{ID}"
```
By: Teoman Deniz [maximum-tension.com](http://maximum-tension.com/)

Use [IX.IO](http://ix.io/) server easily with this program.
You can create, edit or delete a page in [IX.IO](http://ix.io/)

## [COMMANDS]
**`/C` `/CREATE` `-C` `-CREATE` `C` `CREATE`** --> Create page with string or existing file

**`/E` `/EDIT` `-E` `-EDIT` `E` `EDIT`** --> Edit page with string or existing file

**`/D` `/DELETE` `-D` `-DELETE` `D` `DELETE`** --> Delete page

**`/R` `/READ` `-R` `-READ` `R` `READ`** --> Read page

**`NOTE:`** If you don't have an user profile on IX.IO, it is going to automatically created!

**`NOTE:`** You can't chose your own page ID

## [CREATE A PAGE]
```
IXIO.exe /CREATE "FILE.txt" "{USERNAME}" "{PASSWORD}"
```

## [EDIT A PAGE]
```
IXIO.exe edit "SOME TEXTS" "{USERNAME}" "{PASSWORD}" "{ID}"
```

## [DELETE A PAGE]
```
IXIO.exe "-D" "{USERNAME}" "{PASSWORD}" "{ID}"
```

## [READ A PAGE]
```
IXIO.exe /R "{ID}"
```

OR
```bat
FOR /F "TOKENS=*" %%# IN ('IXIO.exe /READ "{ID}"') DO (ECHO %%#)
```

You can save the ID of your new page with:

```bat
FOR /F %%# IN ('IXIO.exe /CREATE "TEST" "USERNAME" "PASSWORD"') DO SET "ID=%%#"
ECHO %ID%
```

![image](https://cdn.discordapp.com/attachments/630843149778157623/946811415677788251/maximum-tension.png)
