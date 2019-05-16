.LOGTABLE vmtest.logtable;

.logon 127.0.0.1/dbc, dbc;

   .BEGIN MLOAD TABLES vmtest.CARD_ACCOUNT_REL;
      .LAYOUT Data;  
		.FIELD in_WH_CARD_NO  * VARCHAR(20) ;
		.FIELD in_WH_ACC_NO  * VARCHAR(20) ;
		.FIELD in_ACC_NO  * VARCHAR(20);
		.FIELD in_CARD_NO  * VARCHAR(20) ;
		.FIELD in_SRCE_CARD_ID  * VARCHAR(20);
		.FIELD in_CARD_ROLE_CDE  * VARCHAR(20);
		.FIELD in_CARD_ACC_ROLE_TYP   * VARCHAR(20);
		.FIELD in_SRCE_SYS   * VARCHAR(20);
		.FIELD in_SRCE_INST   * VARCHAR(20);
		.FIELD in_LOAD_LAST_ACTION  * VARCHAR(20) ;
		.FIELD in_LOAD_DTE   * VARCHAR(20) ;
		.FIELD in_LOAD_TIME   * VARCHAR(20) ;

      .DML LABEL DataLabel;
      INSERT INTO vmtest.CARD_ACCOUNT_REL
      VALUES (
		:in_WH_CARD_NO,
		:in_WH_ACC_NO,
		:in_ACC_NO,
		:in_CARD_NO,
		:in_SRCE_CARD_ID,
		:in_CARD_ROLE_CDE,
		:in_CARD_ACC_ROLE_TYP ,
		:in_SRCE_SYS ,
		:in_SRCE_INST ,
		:in_LOAD_LAST_ACTION,
		:in_LOAD_DTE ,
		:in_LOAD_TIME
      );
      .IMPORT INFILE ../dane_testowe/CARD_ACCOUNT_REL_DATA_FILE.dat
      FORMAT VARTEXT ''
      LAYOUT Data
      APPLY DataLabel;  
   .END MLOAD;  
LOGOFF;

