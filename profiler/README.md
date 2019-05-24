# Hurtownia danych w chmurze
## Przydatne linki
- Teradata (TDExpress16.20_Sles11_20181108052529.7z,
wersja 40Gb http://downloads.teradata.com/download/files/7671/200501/0/TDExpress16.10_Sles11_40GB.7z):
http://downloads.teradata.com/download/database/teradata-express-for-vmware-player
- VMWare:
http://download3.vmware.com/software/player/file/VMware-player-15.0.2-10952284.exe
- Tworzenie tabel
https://downloads.teradata.com/database/articles/teradata-express-14-0-for-vmware-user-guide
- Tworzenie użytkownika
https://docs.teradata.com/reader/u8~Pwz3BmiO8RrPCsqF7bQ/SeSeMcCgpZjIY5~i3Ky8cw
- Python teradata module: https://pypi.org/project/teradata/
- Windows ODBC teradata driver: http://downloads.teradata.com/download/connectivity/odbc-driver/windows

## Inicjalizacja
### Utworzenie użytkownika vmtest
By utworzyć użytkownika vmtest uruchom skrypt ```CREATE_USER.btq```

### Tworzenie tabel w bazie danych
By utworzyć tabele w bazie danych uruchom skrypt ```CREATE_TABLES.btq```
- Pliki z definicjami tabel powinny znajdować się w podkatalogu Tables_Definitions katalogu zawierającego plik ```CREATE_TABLES.btq```

### Usuwanie wszystkich tabel
By usunąć wszystkie tabele z bazy danych uruchom skrypt ```DROP_ALL.btq``` 

### Wstawianie danych do tabeli
https://www.tutorialspoint.com/teradata/teradata_multiload.htm
Link do skryptów ładujących dane (hasło: wJ7dB8):
https://drive.google.com/open?id=1rYOc-UX01f2yyX0-_gD5v-LLTbAE-3yI
Użycie skryptów: ```mload < “plik ze skryptem”```

Struktura katalogów:
- data_insertion_scripts - katalog ze skryptam mload
- dane_testowe - katalog z plikami dat

Przykład skryptu ładującego dane do tabeli ACC_ICBS_CURRENT_PERIODIC z użyciem mload:
```
.LOGTABLE vmtest.logtable;

.logon 127.0.0.1/dbc, dbc;

   .BEGIN MLOAD TABLES vmtest.ACCOUNT_ICBS_DEPOSIT_PERIODIC;
  	.LAYOUT Data;  
   	 .FIELD in_WH_ACC_NO  * VARCHAR(30) ;
   	 .FIELD in_ACC_NO  * VARCHAR(16) ;
   	 .FIELD in_APPROVAL_CDE  * VARCHAR(1) ;
   	 .FIELD in_INTEREST_INDEX_NO  * VARCHAR(30) ;
   	 .FIELD in_ACCRUAL_CDE  * VARCHAR(1) ;
   	 .FIELD in_INT_TYP_CDE  * VARCHAR(1) ;
   	 .FIELD in_PRNCPL_CR_INT_MAX_RTE  * VARCHAR(30);
   	 .FIELD in_PRNCPL_CR_INT_MIN_RTE  * VARCHAR(30);
   	 .FIELD in_IDX_PRNCPL_VARIANCE_RTE  * VARCHAR(30);
   	 .FIELD in_TERMINATION_DTE  * VARCHAR(30) ;
   	 .FIELD in_PAID_CR_INT_AMT  * VARCHAR(30);
   	 .FIELD in_PAID_CR_INT_REF_CRNCY_AMT  * VARCHAR(30);
   	 .FIELD in_ORIG_DEPOSIT_AMT  * VARCHAR(30);
   	 .FIELD in_STMT_FREQ_CNT  * VARCHAR(20) ;
   	 .FIELD in_STMT_FREQ_PERIOD_CDE  * VARCHAR(1) ;
   	 .FIELD in_STMT_ACC_IND  * VARCHAR(1) ;
   	 .FIELD in_RECOVERY_PROCESS_IND  * VARCHAR(1) ;
   	 .FIELD in_CONTRACT_EFF_TMSTMP  * VARCHAR(200);
   	 .FIELD in_LAST_RENEWAL_DTE  * VARCHAR(1000) ;
   	 .FIELD in_RENEWAL_CNT  * VARCHAR(600) ;
   	 .FIELD in_INT_PMT_FREQ_CNT  * VARCHAR(2000) ;
   	 .FIELD in_INT_PMT_FREQ_PERIOD_CDE  * VARCHAR(1) ;
   	 .FIELD in_RENEWAL_IND  * VARCHAR(1) ;
   	 .FIELD in_SRCE_NBP_CLS_CDE  * VARCHAR(3) ;
   	 .FIELD in_STAFF_OPEN_ID  * VARCHAR(20) ;
   	 .FIELD in_STAFF_OPEN_SKP_NO  * VARCHAR(30);
   	 .FIELD in_STAFF_OPEN_BRANCH_NO  * VARCHAR(5) ;
   	 .FIELD in_STAFF_CLOSE_SKP_NO  * VARCHAR(30);
   	 .FIELD in_STAFF_CLOSE_BRANCH_NO  * VARCHAR(5) ;
   	 .FIELD in_LAST_INT_PERIOD_DTE  * VARCHAR(30) ;
   	 .FIELD in_NXT_INT_PMT_DTE  * VARCHAR(30) ;
   	 .FIELD in_INT_STAT_CDE  * VARCHAR(1) ;
   	 .FIELD in_INT_RTE_FREQ_PERIOD_CDE  * VARCHAR(1) ;
   	 .FIELD in_INT_RTE_FREQ_CNT  * VARCHAR(20) ;
   	 .FIELD in_INT_RTE_REVIEW_DAY_NO  * VARCHAR(20) ;
   	 .FIELD in_NXT_RESET_DTE  * VARCHAR(30) ;
   	 .FIELD in_PREV_RTE_RESET_DTE  * VARCHAR(30) ;
   	 .FIELD in_LAST_RENEWAL_BAL_AMT  * VARCHAR(30);
   	 .FIELD in_LAST_CR_BAL_AMT  * VARCHAR(30);
   	 .FIELD in_LAST_CR_BAL_DTE  * VARCHAR(30) ;
   	 .FIELD in_MATRIX_NO  * VARCHAR(30);
   	 .FIELD in_PERIOD_DTE  * VARCHAR(30) ;
   	 .FIELD in_SRCE_SYS  * VARCHAR(20) ;
   	 .FIELD in_SRCE_INST  * VARCHAR(20) ;
   	 .FIELD in_LOAD_LAST_ACTION  * VARCHAR(1) ;
   	 .FIELD in_LOAD_DTE  * VARCHAR(30) ;
   	 .FIELD in_LOAD_TIME * VARCHAR(30);

  	.DML LABEL DataLabel;
  	INSERT INTO vmtest.ACCOUNT_ICBS_DEPOSIT_PERIODIC
  	VALUES (
   	 :in_WH_ACC_NO  ,
   	 :in_ACC_NO  ,
   	 :in_APPROVAL_CDE  ,
   	 :in_INTEREST_INDEX_NO  ,
   	 :in_ACCRUAL_CDE  ,
   	 :in_INT_TYP_CDE  ,
   	 :in_PRNCPL_CR_INT_MAX_RTE  ,
   	 :in_PRNCPL_CR_INT_MIN_RTE  ,
   	 :in_IDX_PRNCPL_VARIANCE_RTE  ,
   	 :in_TERMINATION_DTE  ,
   	 :in_PAID_CR_INT_AMT  ,
   	 :in_PAID_CR_INT_REF_CRNCY_AMT  ,
   	 :in_ORIG_DEPOSIT_AMT  ,
   	 :in_STMT_FREQ_CNT  ,
   	 :in_STMT_FREQ_PERIOD_CDE  ,
   	 :in_STMT_ACC_IND  ,
   	 :in_RECOVERY_PROCESS_IND  ,
   	 :in_CONTRACT_EFF_TMSTMP  ,
   	 :in_LAST_RENEWAL_DTE  ,
   	 :in_RENEWAL_CNT  ,
   	 :in_INT_PMT_FREQ_CNT  ,
   	 :in_INT_PMT_FREQ_PERIOD_CDE  ,
   	 :in_RENEWAL_IND  ,
   	 :in_SRCE_NBP_CLS_CDE  ,
   	 :in_STAFF_OPEN_ID  ,
   	 :in_STAFF_OPEN_SKP_NO  ,
   	 :in_STAFF_OPEN_BRANCH_NO  ,
   	 :in_STAFF_CLOSE_SKP_NO  ,
   	 :in_STAFF_CLOSE_BRANCH_NO  ,
   	 :in_LAST_INT_PERIOD_DTE  ,
   	 :in_NXT_INT_PMT_DTE  ,
   	 :in_INT_STAT_CDE  ,
   	 :in_INT_RTE_FREQ_PERIOD_CDE  ,
   	 :in_INT_RTE_FREQ_CNT  ,
   	 :in_INT_RTE_REVIEW_DAY_NO  ,
   	 :in_NXT_RESET_DTE  ,
   	 :in_PREV_RTE_RESET_DTE  ,
   	 :in_LAST_RENEWAL_BAL_AMT  ,
   	 :in_LAST_CR_BAL_AMT  ,
   	 :in_LAST_CR_BAL_DTE  ,
   	 :in_MATRIX_NO  ,
   	 :in_PERIOD_DTE  ,
   	 :in_SRCE_SYS  ,
   	 :in_SRCE_INST  ,
   	 :in_LOAD_LAST_ACTION  ,
   	 :in_LOAD_DTE  ,
   	 :in_LOAD_TIME
  	);
  	.IMPORT INFILE ../dane_testowe/ACCOUNT_ICBS_DEPOSIT_PERIODIC_DATA_FILE.dat
  	FORMAT VARTEXT ''
  	LAYOUT Data
  	APPLY DataLabel;  
   .END MLOAD;  
LOGOFF;
```

### Miary dla poszczególnych typów
```
ONCE: COUNT(*) as record_count
I, F, D: record_count-COUNT(%col%) AS %col%_nulls, COUNT(DISTINCT %col%) AS %col%_distincts, MIN(%col%) %col%_minimum, MAX(%col%) as %col%_maximum, SUM(%col%) as %col%_sum, ROUND(STDDEV_POP(%col%), 2) as %col%_standard_deviation, AVG(%col%) as %col%_mean
CV:  record_count-COUNT(%col%) AS %col%_nulls, COUNT(DISTINCT %col%) AS %col%_distincts, SUM(CASE %col% WHEN '' THEN 1 ELSE 0 END) AS %col%_empties, SUM(CASE TRIM(%col%) WHEN '' THEN 1 ELSE 0 END) AS %col%_blanks, AVG(LENGTH(%col%)), MIN(LENGTH(%col%)), MAX(LENGTH(%col%))
CF, BF, BV: record_count-COUNT(%col%) AS %col%_nulls, COUNT(DISTINCT %col%) AS %col%_distincts
```

### Pobieranie wszystkich nazw kolumn wraz z typami
By pobrać wszystkie kolumny wraz z typami uruchom skrypt ```SHOW_ALL_TABLES.btq```

## Wykonywanie programu
### Przygotowanie (windows)
Jesli maszyna TeraData jest juz uruchomiona i odpowiednio skonfigurowana, mozemy przystapic do konfiguracji polaczenia z maszyna wirtualna.
W tym celu nalezy najpierw zainstalowac sterownik ODBC TeraData (link u gory).

### Zestawianie polaczenia
Po zainstalowaniu wykonujemy nastepujące kroki:
- Uruchom aplet Administrator ODBC
- Aby dodać nowe połączenie liknij "Dodaj"
- Z listy wybierz Teradata Database ODBC Driver i klinij "Zakończ"
- Wypełnij pola kreatora
* W polu "Name" wpisz nazwe swojego polaczenia (pamietaj, aby zgadzla sie ona z konfiguracja w pliku `udaexec.ini`.
* W polu "Name or IP address" wpisz adres IP swojej maszyny wirtualnej Teradata
* Uzupełnij pola "Username" i "Password"
Przykładowa konfiguracja:
![Przykladowa konfiguracja](konfiguracja.PNG)

- klinkij "OK' aby zakonczyc konfiguracje

### Uruchamianie skryptu
Jesli konfiguracja jest poprawna skrpyt powinien wykonac sie bez problemu po wpisaniu ponizszej komendy:
```python app.py```

Aby wyswietlic liste dostepnych parametrow, wpisz:
```python app.py --help```