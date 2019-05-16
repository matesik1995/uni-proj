.LOGTABLE vmtest.logtable;

.logon 127.0.0.1/dbc, dbc;

   .BEGIN MLOAD TABLES vmtest.ACC_ICBS_CURRENT_PERIODIC;  
      .LAYOUT Data;  
        .FIELD in_WH_ACC_NO  * VARCHAR(20)  ;
        .FIELD in_ACC_NO  * VARCHAR(16) ;
        .FIELD in_ACCRD_INT_CR_AMT  * VARCHAR(30);
        .FIELD in_ACCRD_INT_DR_AMT  * VARCHAR(30);
        .FIELD in_PROVSN_DTE  * VARCHAR(20);
        .FIELD in_PROVSN_ARREARS_AMT  * VARCHAR(30);
        .FIELD in_BAD_DEBT_IND  * VARCHAR(1) ;
        .FIELD in_CA_SRCE_PROD_CDE  * VARCHAR(3) ;
        .FIELD in_ACC_NSC  * VARCHAR(8) ;
        .FIELD in_BD_SETUP_DTE  * VARCHAR(20);
        .FIELD in_INTEREST_PLAN_NO  * VARCHAR(5) ;
        .FIELD in_INTEREST_ARREARS_AMT  * VARCHAR(30);
        .FIELD in_PRINCIPAL_ARREARS_AMT  * VARCHAR(30);
        .FIELD in_PRINCIPAL_BALANCE_AMT  * VARCHAR(30);
        .FIELD in_AVG_MTH_CR_BAL_AMT  * VARCHAR(30);
        .FIELD in_AVG_MTH_DR_BAL_AMT  * VARCHAR(30);
        .FIELD in_RESTRUCTURING_CDE  * VARCHAR(20) ;
        .FIELD in_RESTR_DTE  * VARCHAR(20);
        .FIELD in_OD_IND  * VARCHAR(1) ;
        .FIELD in_OD_BEG_DTE  * VARCHAR(20);
        .FIELD in_AVAIL_BAL_AMT  * VARCHAR(30);
        .FIELD in_CORP_ORG_UNIT_CDE  * VARCHAR(18) ;
        .FIELD in_PAST_DUE_DAYS_CNT  * VARCHAR(20) ;
        .FIELD in_ACCRUAL_CDE  * VARCHAR(1) ;
        .FIELD in_PRNCPL_ACCRD_DR_INT_AMT  * VARCHAR(30);
        .FIELD in_PRNCPL_ARREARS_ACCRD_INT_AMT  * VARCHAR(30);
        .FIELD in_PRNCPL_ARREARS_INT_RTE  * VARCHAR(30);
        .FIELD in_INT_RATE_OD_IDX_NO  * VARCHAR(20) ;
        .FIELD in_INT_RATE_DR_IDX_NO  * VARCHAR(20) ;
        .FIELD in_INT_RATE_CR_IDX_NO  * VARCHAR(20) ;
        .FIELD in_IDX_PRNCPL_VARIANCE_RTE  * VARCHAR(30);
        .FIELD in_IDX_ARREARS_VARIANCE_RTE  * VARCHAR(30);
        .FIELD in_SRCE_SYS_PROD_EXT_CDE  * VARCHAR(2) ;
        .FIELD in_INC_PAID_INT_AMT  * VARCHAR(30);
        .FIELD in_INC_PAID_INT_REF_CRNCY_AMT  * VARCHAR(30);
        .FIELD in_PAID_CR_INT_AMT  * VARCHAR(30);
        .FIELD in_PAID_CR_INT_REF_CRNCY_AMT  * VARCHAR(30);
        .FIELD in_PRNCPL_DR_INT_RTE  * VARCHAR(30);
        .FIELD in_PRNCPL_CR_INT_RTE  * VARCHAR(30);
        .FIELD in_CASHPOOL_IND  * VARCHAR(1) ;
        .FIELD in_ACCRUAL_CR_CDE  * VARCHAR(1) ;
        .FIELD in_ACCRUAL_OD_CDE  * VARCHAR(1) ;
        .FIELD in_AUTO_OD_RENEWAL_IND  * VARCHAR(1) ;
        .FIELD in_STMT_FREQ_CNT  * VARCHAR(20) ;
        .FIELD in_STMT_FREQ_PERIOD_CDE  * VARCHAR(1) ;
        .FIELD in_STMT_ACC_IND  * VARCHAR(1) ;
        .FIELD in_STMT_TYPE_CDE  * VARCHAR(20) ;
        .FIELD in_RECOVERY_PROCESS_IND  * VARCHAR(1) ;
        .FIELD in_INT_PMT_FREQ_CNT  * VARCHAR(20) ;
        .FIELD in_INT_PMT_FREQ_PERIOD_CDE  * VARCHAR(1) ;
        .FIELD in_ADDN_RTE_FREQ_CNT  * VARCHAR(20) ;
        .FIELD in_ADDN_INT_RTE_FREQ_PERIOD_CDE  * VARCHAR(1) ;
        .FIELD in_FEE_FREQ_PERIOD_CDE  * VARCHAR(1) ;
        .FIELD in_FEE_FREQ_CNT  * VARCHAR(3) ;
        .FIELD in_FEE_PROMOTION_CDE  * VARCHAR(3) ;
        .FIELD in_SRCE_NBP_CLS_CDE  * VARCHAR(3) ;
        .FIELD in_INTRADAY_LIMIT_AMT  * VARCHAR(30);
        .FIELD in_INTRADAY_LIMIT_CDE  * VARCHAR(1) ;
        .FIELD in_INTRADAY_LIMIT_END_DTE  * VARCHAR(20);
        .FIELD in_INTRADAY_PERMIS_DPSTD_CNT  * VARCHAR(20) ;
        .FIELD in_CURR_AGREEMENT_NO  * VARCHAR(30) ;
        .FIELD in_UNPAID_OD_INT_FEE_AMT  * VARCHAR(30);
        .FIELD in_UNPAID_OD_INT_AMT  * VARCHAR(30);
        .FIELD in_OD_EFF_DTE  * VARCHAR(20);
        .FIELD in_CR_TURNOVER_AMT  * VARCHAR(30);
        .FIELD in_PREV_CR_TURNOVER_AMT  * VARCHAR(30);
        .FIELD in_STAFF_OPEN_ID  * VARCHAR(20) ;
        .FIELD in_STAFF_OPEN_SKP_NO  * VARCHAR(20) ;
        .FIELD in_REG_PAYMENT_AMT  * VARCHAR(30);
        .FIELD in_OVERLIMIT_BEG_DTE  * VARCHAR(20);
        .FIELD in_SPECIFIC_INT_IND  * VARCHAR(1) ;
        .FIELD in_INT_INCR_TYP_CDE  * VARCHAR(1) ;
        .FIELD in_INT_INCR_SUB_TYP_CDE  * VARCHAR(10) ;
        .FIELD in_LIMIT_CHNL_TYP  * VARCHAR(1) ;
        .FIELD in_OD_PURPOSE_PKD_CDE  * VARCHAR(20) ;
        .FIELD in_ANNEX_SIGN_DTE  * VARCHAR(20);
        .FIELD in_BFG_IND  * VARCHAR(1) ;
        .FIELD in_LAST_CR_BAL_AMT  * VARCHAR(30);
        .FIELD in_LAST_CR_BAL_DTE  * VARCHAR(20);
        .FIELD in_LAST_DR_BAL_AMT  * VARCHAR(30);
        .FIELD in_LAST_DR_BAL_DTE  * VARCHAR(20);
        .FIELD in_PROG_INTEREST_PLAN_NO  * VARCHAR(5) ;
        .FIELD in_SALARY_IND  * VARCHAR(1) ;
        .FIELD in_PERIOD_DTE  * VARCHAR(20)  ;
        .FIELD in_SRCE_SYS  * VARCHAR(20)  ;
        .FIELD in_SRCE_INST  * VARCHAR(20)  ;
        .FIELD in_LOAD_LAST_ACTION  * VARCHAR(1)  ;
        .FIELD in_LOAD_DTE  * VARCHAR(20)  ;
        .FIELD in_LOAD_TIME * VARCHAR(20);

      .DML LABEL DataLabel;
      INSERT INTO vmtest.ACC_ICBS_CURRENT_PERIODIC
      VALUES (
        :in_WH_ACC_NO,
        :in_ACC_NO,
        :in_ACCRD_INT_CR_AMT,
        :in_ACCRD_INT_DR_AMT,
        :in_PROVSN_DTE,
        :in_PROVSN_ARREARS_AMT,
        :in_BAD_DEBT_IND,
        :in_CA_SRCE_PROD_CDE,
        :in_ACC_NSC,
        :in_BD_SETUP_DTE,
        :in_INTEREST_PLAN_NO,
        :in_INTEREST_ARREARS_AMT,
        :in_PRINCIPAL_ARREARS_AMT,
        :in_PRINCIPAL_BALANCE_AMT,
        :in_AVG_MTH_CR_BAL_AMT,
        :in_AVG_MTH_DR_BAL_AMT,
        :in_RESTRUCTURING_CDE,
        :in_RESTR_DTE,
        :in_OD_IND,
        :in_OD_BEG_DTE,
        :in_AVAIL_BAL_AMT,
        :in_CORP_ORG_UNIT_CDE,
        :in_PAST_DUE_DAYS_CNT,
        :in_ACCRUAL_CDE,
        :in_PRNCPL_ACCRD_DR_INT_AMT,
        :in_PRNCPL_ARREARS_ACCRD_INT_AMT,
        :in_PRNCPL_ARREARS_INT_RTE,
        :in_INT_RATE_OD_IDX_NO,
        :in_INT_RATE_DR_IDX_NO,
        :in_INT_RATE_CR_IDX_NO,
        :in_IDX_PRNCPL_VARIANCE_RTE,
        :in_IDX_ARREARS_VARIANCE_RTE,
        :in_SRCE_SYS_PROD_EXT_CDE,
        :in_INC_PAID_INT_AMT,
        :in_INC_PAID_INT_REF_CRNCY_AMT,
        :in_PAID_CR_INT_AMT,
        :in_PAID_CR_INT_REF_CRNCY_AMT,
        :in_PRNCPL_DR_INT_RTE,
        :in_PRNCPL_CR_INT_RTE,
        :in_CASHPOOL_IND,
        :in_ACCRUAL_CR_CDE,
        :in_ACCRUAL_OD_CDE,
        :in_AUTO_OD_RENEWAL_IND,
        :in_STMT_FREQ_CNT,
        :in_STMT_FREQ_PERIOD_CDE,
        :in_STMT_ACC_IND,
        :in_STMT_TYPE_CDE,
        :in_RECOVERY_PROCESS_IND,
        :in_INT_PMT_FREQ_CNT,
        :in_INT_PMT_FREQ_PERIOD_CDE,
        :in_ADDN_RTE_FREQ_CNT,
        :in_ADDN_INT_RTE_FREQ_PERIOD_CDE,
        :in_FEE_FREQ_PERIOD_CDE,
        :in_FEE_FREQ_CNT,
        :in_FEE_PROMOTION_CDE,
        :in_SRCE_NBP_CLS_CDE,
        :in_INTRADAY_LIMIT_AMT,
        :in_INTRADAY_LIMIT_CDE,
        :in_INTRADAY_LIMIT_END_DTE,
        :in_INTRADAY_PERMIS_DPSTD_CNT,
        :in_CURR_AGREEMENT_NO,
        :in_UNPAID_OD_INT_FEE_AMT,
        :in_UNPAID_OD_INT_AMT,
        :in_OD_EFF_DTE,
        :in_CR_TURNOVER_AMT,
        :in_PREV_CR_TURNOVER_AMT,
        :in_STAFF_OPEN_ID,
        :in_STAFF_OPEN_SKP_NO,
        :in_REG_PAYMENT_AMT,
        :in_OVERLIMIT_BEG_DTE,
        :in_SPECIFIC_INT_IND,
        :in_INT_INCR_TYP_CDE,
        :in_INT_INCR_SUB_TYP_CDE,
        :in_LIMIT_CHNL_TYP,
        :in_OD_PURPOSE_PKD_CDE,
        :in_ANNEX_SIGN_DTE,
        :in_BFG_IND,
        :in_LAST_CR_BAL_AMT,
        :in_LAST_CR_BAL_DTE,
        :in_LAST_DR_BAL_AMT,
        :in_LAST_DR_BAL_DTE,
        :in_PROG_INTEREST_PLAN_NO,
        :in_SALARY_IND,
        :in_PERIOD_DTE,
        :in_SRCE_SYS,
        :in_SRCE_INST,
        :in_LOAD_LAST_ACTION,
        :in_LOAD_DTE,
        :in_LOAD_TIME
      );
      .IMPORT INFILE ../dane_testowe/ACC_ICBS_CURRENT_PERIODIC_DATA_FILE.dat
      FORMAT VARTEXT ''
      LAYOUT Data
      APPLY DataLabel;  
   .END MLOAD;  
LOGOFF;

