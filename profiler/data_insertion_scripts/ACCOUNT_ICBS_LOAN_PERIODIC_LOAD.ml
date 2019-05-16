.LOGTABLE vmtest.logtable;

.logon 127.0.0.1/dbc, dbc;

   .BEGIN MLOAD TABLES vmtest.ACCOUNT_ICBS_LOAN_PERIODIC;
      .LAYOUT Data;  
		.FIELD in_WH_ACC_NO  * VARCHAR(30);
		.FIELD in_ACC_NO  * VARCHAR(16); 
		.FIELD in_NXT_LN_PMT_DTE  * VARCHAR(20); 
		.FIELD in_PROVSN_DTE  * VARCHAR(20); 
		.FIELD in_PROVSN_ARREARS_AMT  * VARCHAR(20);
		.FIELD in_WRITE_OFF_IND  * VARCHAR(1); 
		.FIELD in_WRITE_OFF_DTE  * VARCHAR(20); 
		.FIELD in_BAD_DEBT_IND  * VARCHAR(1); 
		.FIELD in_AVAIL_BAL_AMT  * VARCHAR(20);
		.FIELD in_SECURITY_HELD_IND  * VARCHAR(1); 
		.FIELD in_CONSEC_REPAYMTS_MISSED  * VARCHAR(20); 
		.FIELD in_REPAYMTS_OUTSTDG  * VARCHAR(20); 
		.FIELD in_PURPOSE_CDE  * VARCHAR(5); 
		.FIELD in_PURPOSE_CHANGE_DTE  * VARCHAR(20); 
		.FIELD in_LA_SRCE_PROD_CDE  * VARCHAR(3); 
		.FIELD in_ACC_NSC  * VARCHAR(8); 
		.FIELD in_BD_SETUP_DTE  * VARCHAR(20); 
		.FIELD in_INTEREST_INDEX_NO  * VARCHAR(30); 
		.FIELD in_WRITE_OFF_AMT  * VARCHAR(20);
		.FIELD in_INTEREST_ARREARS_AMT  * VARCHAR(20);
		.FIELD in_PRINCIPAL_ARREARS_AMT  * VARCHAR(20);
		.FIELD in_PRINCIPAL_BALANCE_AMT  * VARCHAR(20);
		.FIELD in_RESTRUCTURING_CDE  * VARCHAR(20); 
		.FIELD in_RESTR_DTE  * VARCHAR(20); 
		.FIELD in_CORP_ORG_UNIT_CDE  * VARCHAR(18); 
		.FIELD in_RECOURSE_CDE  * VARCHAR(1); 
		.FIELD in_PAST_DUE_DAYS_CNT  * VARCHAR(20); 
		.FIELD in_REVOLVING_IND  * VARCHAR(1); 
		.FIELD in_DISBURSED_AMT  * VARCHAR(20);
		.FIELD in_DISBURSEMENT_ACC_NO  * VARCHAR(26); 
		.FIELD in_ACCRUAL_CDE  * VARCHAR(1); 
		.FIELD in_FIRST_AMORT_DTE  * VARCHAR(20); 
		.FIELD in_TOT_REPAYMTS_AMT  * VARCHAR(20);
		.FIELD in_LAST_REPAYMT_DTE  * VARCHAR(20); 
		.FIELD in_ONGOING_SCR_DTE  * VARCHAR(20); 
		.FIELD in_ONGOING_SCR_NO  * VARCHAR(20); 
		.FIELD in_SCR_CARD_CDE  * VARCHAR(50); 
		.FIELD in_PD_RTE  * VARCHAR(20);
		.FIELD in_ORIG_MATURITY_MTH_CNT  * VARCHAR(20);
		.FIELD in_PRNCPL_ARREARS_INT_RTE  * VARCHAR(20);
		.FIELD in_PRNCPL_ACCRD_DR_INT_AMT  * VARCHAR(20);
		.FIELD in_PRNCPL_ARREARS_ACCRD_INT_AMT  * VARCHAR(20);
		.FIELD in_INT_ARREARS_IDX_NO  * VARCHAR(30); 
		.FIELD in_INT_TYP_CDE  * VARCHAR(1); 
		.FIELD in_TERMINATION_DTE  * VARCHAR(20); 
		.FIELD in_INC_PAID_INT_AMT  * VARCHAR(20);
		.FIELD in_INC_PAID_INT_REF_CRNCY_AMT  * VARCHAR(20);
		.FIELD in_MARGIN_PROMOTION_CHG_DTE  * VARCHAR(20); 
		.FIELD in_MARGIN_PROMOTION_NXT_RTE  * VARCHAR(20);
		.FIELD in_PRNCPL_DR_INT_RTE  * VARCHAR(20);
		.FIELD in_PRNCPL_DR_INT_MIN_RTE  * VARCHAR(20);
		.FIELD in_ACCRUAL_ARREARS_CDE  * VARCHAR(1); 
		.FIELD in_SUBSIDIZED_LOAN_IND  * VARCHAR(1); 
		.FIELD in_SUBSIDIZED_LOAN_CDE  * VARCHAR(10); 
		.FIELD in_LN_AGREEMENT_NO  * VARCHAR(22); 
		.FIELD in_PMT_FREQ_PERIOD_CDE  * VARCHAR(1); 
		.FIELD in_PMT_FREQ_CNT  * VARCHAR(20); 
		.FIELD in_CONV_ACC_OLD_NO  * VARCHAR(16); 
		.FIELD in_RECVRY_ACC_NO  * VARCHAR(16); 
		.FIELD in_EFF_INT_RTE  * VARCHAR(20);
		.FIELD in_FIRST_DISBURSEMENT_DTE  * VARCHAR(20); 
		.FIELD in_LGD_BEST_FIT_RTE  * VARCHAR(20);
		.FIELD in_LGD_DOWN_TURN_RTE  * VARCHAR(20);
		.FIELD in_LGD_MODEL_CDE  * VARCHAR(6); 
		.FIELD in_LGD_BEEL_RTE  * VARCHAR(20);
		.FIELD in_LGD_UNEXPECTED_LOSS_RTE  * VARCHAR(20);
		.FIELD in_RECVRY_MONITORING_FEE_AMT  * VARCHAR(20);
		.FIELD in_RECVRY_MONIT_PAID_FEE_AMT  * VARCHAR(20);
		.FIELD in_PPI_IND  * VARCHAR(1); 
		.FIELD in_ACTUAL_PMT_SCHEDULE_TYP  * VARCHAR(1); 
		.FIELD in_SRCE_NBP_CLS_CDE  * VARCHAR(3); 
		.FIELD in_DISBURSED_INT_RTE  * VARCHAR(20);
		.FIELD in_PAYMENT_BANK_HOLIDAY_CDE  * VARCHAR(1); 
		.FIELD in_ORIG_PAYMENT_DTE  * VARCHAR(20); 
		.FIELD in_NEXT_INT_PAYMENT_DTE  * VARCHAR(20); 
		.FIELD in_INT_RTE_BGK_INDEX_NO  * VARCHAR(5); 
		.FIELD in_CURR_INT_RTE_BGK_RTE  * VARCHAR(20);
		.FIELD in_SUBSIDIZED_INT_BGK_AMT  * VARCHAR(20);
		.FIELD in_COMMISSION_BFG_CDE  * VARCHAR(1); 
		.FIELD in_SPECIAL_OFFER_CDE  * VARCHAR(2); 
		.FIELD in_LOAN_HOLIDAY_DTE  * VARCHAR(20); 
		.FIELD in_SEC_REPAYMENT_ACC_NO  * VARCHAR(28); 
		.FIELD in_FIRST_REPAYMENT_ACC_NO  * VARCHAR(28); 
		.FIELD in_STAFF_OPEN_ID  * VARCHAR(20); 
		.FIELD in_STAFF_OPEN_SKP_NO  * VARCHAR(30);
		.FIELD in_FEE_BASE_RTE  * VARCHAR(20);
		.FIELD in_FEE_DISC_RTE  * VARCHAR(20);
		.FIELD in_FEE_DISC_AMT  * VARCHAR(20);
		.FIELD in_SUBSIDIZED_BGK_EXPIRY_DTE  * VARCHAR(20); 
		.FIELD in_EXPIRED_SUBSIDIZED_PAYMENT_AMT  * VARCHAR(20);
		.FIELD in_MAX_INTEREST_RTE  * VARCHAR(20);
		.FIELD in_MAX_INTEREST_RTE_END_DTE  * VARCHAR(20); 
		.FIELD in_RENEWAL_IND  * VARCHAR(1); 
		.FIELD in_LAST_RENEWAL_DTE  * VARCHAR(20); 
		.FIELD in_IDX_PRNCPL_VARIANCE_RTE  * VARCHAR(20);
		.FIELD in_IDX_PRNCPL_MLTP_RTE  * VARCHAR(20);
		.FIELD in_INT_RTE_FREQ_PERIOD_CDE  * VARCHAR(1); 
		.FIELD in_INT_RTE_FREQ_CNT  * VARCHAR(20);
		.FIELD in_INT_RTE_REVIEW_DAY_NO  * VARCHAR(20);
		.FIELD in_NXT_RESET_DTE  * VARCHAR(20); 
		.FIELD in_PREV_RTE_RESET_DTE  * VARCHAR(20); 
		.FIELD in_LOCKOUT_MTH_CNT  * VARCHAR(20);
		.FIELD in_INT_INCR_TYP_CDE  * VARCHAR(1); 
		.FIELD in_INT_INCR_SUB_TYP_CDE  * VARCHAR(10); 
		.FIELD in_ANNEX_SIGN_DTE  * VARCHAR(20); 
		.FIELD in_PMT_SCHEDULE_DAY_NO  * VARCHAR(20); 
		.FIELD in_ADDN_INT_RTE_FREQ_PERIOD_CDE  * VARCHAR(1); 
		.FIELD in_ADDN_RTE_FREQ_CNT  * VARCHAR(20); 
		.FIELD in_ADDN_INT_PMT_DAY_NO  * VARCHAR(20); 
		.FIELD in_NXT_INT_PMT_DTE  * VARCHAR(20); 
		.FIELD in_NEXT_INT_PERIOD_DTE  * VARCHAR(20); 
		.FIELD in_LAST_INT_PERIOD_DTE  * VARCHAR(20); 
		.FIELD in_PAST_DUE_DTE  * VARCHAR(20); 
		.FIELD in_CONV_ACC_NEW_NO  * VARCHAR(16); 
		.FIELD in_CONV_REASON_CDE  * VARCHAR(1); 
		.FIELD in_CONV_ACC_NEW_2_NO  * VARCHAR(16); 
		.FIELD in_CONV_REASON_2_CDE  * VARCHAR(1); 
		.FIELD in_CONV_ACC_NEW_3_NO  * VARCHAR(16); 
		.FIELD in_CONV_ACC_NEW_4_NO  * VARCHAR(16); 
		.FIELD in_CONV_ACC_NEW_5_NO  * VARCHAR(16); 
		.FIELD in_PENALTY_INT_PAID_AMT  * VARCHAR(20);
		.FIELD in_CONTRACTUAL_INT_PAID_AMT  * VARCHAR(20);
		.FIELD in_CONTRACTUAL_DISC_INT_PAID_AMT  * VARCHAR(20);
		.FIELD in_INT_NOT_PAID_AMT  * VARCHAR(20);
		.FIELD in_MAX_MTH_DPSTD_CNT  * VARCHAR(20); 
		.FIELD in_UNPAID_LN_INT_AMT  * VARCHAR(20);
		.FIELD in_UNPAID_FEE_INCOME_AMT  * VARCHAR(20);
		.FIELD in_CRNCY_BUFFER_IND  * VARCHAR(1); 
		.FIELD in_FWD_RATE_CONVSN  * VARCHAR(20);
		.FIELD in_LN_PURPOSE_PKD_CDE  * VARCHAR(20); 
		.FIELD in_LN_DEVEL_IND  * VARCHAR(1); 
		.FIELD in_EXCLUSION_MTH_CNT  * VARCHAR(20); 
		.FIELD in_LEVEL_PMT_AMT  * VARCHAR(20);
		.FIELD in_ORIG_MATURITY_DTE  * VARCHAR(20); 
		.FIELD in_PMT_REVIEW_PERIOD_CDE  * VARCHAR(1); 
		.FIELD in_ACCRUAL_BASIS_CDE  * VARCHAR(1); 
		.FIELD in_CALC_SCHED_BAL_CDE  * VARCHAR(1); 
		.FIELD in_PREPMT_PRNCPL_IND  * VARCHAR(1); 
		.FIELD in_PERIOD_DTE  * VARCHAR(20); 
		.FIELD in_SRCE_SYS  * VARCHAR(20); 
		.FIELD in_SRCE_INST  * VARCHAR(20); 
		.FIELD in_LOAD_LAST_ACTION  * VARCHAR(1); 
		.FIELD in_LOAD_DTE  * VARCHAR(20); 
		.FIELD in_LOAD_TIME  * VARCHAR(20); 

      .DML LABEL DataLabel;
      INSERT INTO vmtest.ACCOUNT_ICBS_LOAN_PERIODIC
      VALUES (
		:in_WH_ACC_NO ,
		:in_ACC_NO ,
		:in_NXT_LN_PMT_DTE ,
		:in_PROVSN_DTE ,
		:in_PROVSN_ARREARS_AMT ,
		:in_WRITE_OFF_IND ,
		:in_WRITE_OFF_DTE ,
		:in_BAD_DEBT_IND ,
		:in_AVAIL_BAL_AMT ,
		:in_SECURITY_HELD_IND ,
		:in_CONSEC_REPAYMTS_MISSED ,
		:in_REPAYMTS_OUTSTDG ,
		:in_PURPOSE_CDE ,
		:in_PURPOSE_CHANGE_DTE ,
		:in_LA_SRCE_PROD_CDE ,
		:in_ACC_NSC ,
		:in_BD_SETUP_DTE ,
		:in_INTEREST_INDEX_NO ,
		:in_WRITE_OFF_AMT ,
		:in_INTEREST_ARREARS_AMT ,
		:in_PRINCIPAL_ARREARS_AMT ,
		:in_PRINCIPAL_BALANCE_AMT ,
		:in_RESTRUCTURING_CDE ,
		:in_RESTR_DTE ,
		:in_CORP_ORG_UNIT_CDE ,
		:in_RECOURSE_CDE ,
		:in_PAST_DUE_DAYS_CNT ,
		:in_REVOLVING_IND ,
		:in_DISBURSED_AMT ,
		:in_DISBURSEMENT_ACC_NO ,
		:in_ACCRUAL_CDE ,
		:in_FIRST_AMORT_DTE ,
		:in_TOT_REPAYMTS_AMT ,
		:in_LAST_REPAYMT_DTE ,
		:in_ONGOING_SCR_DTE ,
		:in_ONGOING_SCR_NO ,
		:in_SCR_CARD_CDE ,
		:in_PD_RTE ,
		:in_ORIG_MATURITY_MTH_CNT ,
		:in_PRNCPL_ARREARS_INT_RTE ,
		:in_PRNCPL_ACCRD_DR_INT_AMT ,
		:in_PRNCPL_ARREARS_ACCRD_INT_AMT ,
		:in_INT_ARREARS_IDX_NO ,
		:in_INT_TYP_CDE ,
		:in_TERMINATION_DTE ,
		:in_INC_PAID_INT_AMT ,
		:in_INC_PAID_INT_REF_CRNCY_AMT ,
		:in_MARGIN_PROMOTION_CHG_DTE ,
		:in_MARGIN_PROMOTION_NXT_RTE ,
		:in_PRNCPL_DR_INT_RTE ,
		:in_PRNCPL_DR_INT_MIN_RTE ,
		:in_ACCRUAL_ARREARS_CDE ,
		:in_SUBSIDIZED_LOAN_IND ,
		:in_SUBSIDIZED_LOAN_CDE ,
		:in_LN_AGREEMENT_NO ,
		:in_PMT_FREQ_PERIOD_CDE ,
		:in_PMT_FREQ_CNT ,
		:in_CONV_ACC_OLD_NO ,
		:in_RECVRY_ACC_NO ,
		:in_EFF_INT_RTE ,
		:in_FIRST_DISBURSEMENT_DTE ,
		:in_LGD_BEST_FIT_RTE ,
		:in_LGD_DOWN_TURN_RTE ,
		:in_LGD_MODEL_CDE ,
		:in_LGD_BEEL_RTE ,
		:in_LGD_UNEXPECTED_LOSS_RTE ,
		:in_RECVRY_MONITORING_FEE_AMT ,
		:in_RECVRY_MONIT_PAID_FEE_AMT ,
		:in_PPI_IND ,
		:in_ACTUAL_PMT_SCHEDULE_TYP ,
		:in_SRCE_NBP_CLS_CDE ,
		:in_DISBURSED_INT_RTE ,
		:in_PAYMENT_BANK_HOLIDAY_CDE ,
		:in_ORIG_PAYMENT_DTE ,
		:in_NEXT_INT_PAYMENT_DTE ,
		:in_INT_RTE_BGK_INDEX_NO ,
		:in_CURR_INT_RTE_BGK_RTE ,
		:in_SUBSIDIZED_INT_BGK_AMT ,
		:in_COMMISSION_BFG_CDE ,
		:in_SPECIAL_OFFER_CDE ,
		:in_LOAN_HOLIDAY_DTE ,
		:in_SEC_REPAYMENT_ACC_NO ,
		:in_FIRST_REPAYMENT_ACC_NO ,
		:in_STAFF_OPEN_ID ,
		:in_STAFF_OPEN_SKP_NO ,
		:in_FEE_BASE_RTE ,
		:in_FEE_DISC_RTE ,
		:in_FEE_DISC_AMT ,
		:in_SUBSIDIZED_BGK_EXPIRY_DTE ,
		:in_EXPIRED_SUBSIDIZED_PAYMENT_AMT ,
		:in_MAX_INTEREST_RTE ,
		:in_MAX_INTEREST_RTE_END_DTE ,
		:in_RENEWAL_IND ,
		:in_LAST_RENEWAL_DTE ,
		:in_IDX_PRNCPL_VARIANCE_RTE ,
		:in_IDX_PRNCPL_MLTP_RTE ,
		:in_INT_RTE_FREQ_PERIOD_CDE ,
		:in_INT_RTE_FREQ_CNT ,
		:in_INT_RTE_REVIEW_DAY_NO ,
		:in_NXT_RESET_DTE ,
		:in_PREV_RTE_RESET_DTE ,
		:in_LOCKOUT_MTH_CNT ,
		:in_INT_INCR_TYP_CDE ,
		:in_INT_INCR_SUB_TYP_CDE ,
		:in_ANNEX_SIGN_DTE ,
		:in_PMT_SCHEDULE_DAY_NO ,
		:in_ADDN_INT_RTE_FREQ_PERIOD_CDE ,
		:in_ADDN_RTE_FREQ_CNT ,
		:in_ADDN_INT_PMT_DAY_NO ,
		:in_NXT_INT_PMT_DTE ,
		:in_NEXT_INT_PERIOD_DTE ,
		:in_LAST_INT_PERIOD_DTE ,
		:in_PAST_DUE_DTE ,
		:in_CONV_ACC_NEW_NO ,
		:in_CONV_REASON_CDE ,
		:in_CONV_ACC_NEW_2_NO ,
		:in_CONV_REASON_2_CDE ,
		:in_CONV_ACC_NEW_3_NO ,
		:in_CONV_ACC_NEW_4_NO ,
		:in_CONV_ACC_NEW_5_NO ,
		:in_PENALTY_INT_PAID_AMT ,
		:in_CONTRACTUAL_INT_PAID_AMT ,
		:in_CONTRACTUAL_DISC_INT_PAID_AMT ,
		:in_INT_NOT_PAID_AMT ,
		:in_MAX_MTH_DPSTD_CNT ,
		:in_UNPAID_LN_INT_AMT ,
		:in_UNPAID_FEE_INCOME_AMT ,
		:in_CRNCY_BUFFER_IND ,
		:in_FWD_RATE_CONVSN ,
		:in_LN_PURPOSE_PKD_CDE ,
		:in_LN_DEVEL_IND ,
		:in_EXCLUSION_MTH_CNT ,
		:in_LEVEL_PMT_AMT ,
		:in_ORIG_MATURITY_DTE ,
		:in_PMT_REVIEW_PERIOD_CDE ,
		:in_ACCRUAL_BASIS_CDE ,
		:in_CALC_SCHED_BAL_CDE ,
		:in_PREPMT_PRNCPL_IND ,
		:in_PERIOD_DTE ,
		:in_SRCE_SYS ,
		:in_SRCE_INST ,
		:in_LOAD_LAST_ACTION ,
		:in_LOAD_DTE ,
		:in_LOAD_TIME
      );
      .IMPORT INFILE ../dane_testowe/ACCOUNT_ICBS_LOAN_PERIODIC_DATA_FILE.dat
      FORMAT VARTEXT ''
      LAYOUT Data
      APPLY DataLabel;  
   .END MLOAD;  
LOGOFF;

