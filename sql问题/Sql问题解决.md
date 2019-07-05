# 1.动态行转不定列

```sql
---动态行转不定列
create or replace procedure p_RowsToCols(as_sql       in varchar2 --源数据的查询sql
                                        ,as_sql_cols  in varchar2 --动态转换列的查询sql,要求转为列的那列，字段名必须为cols，支持排序
                                        ,as_aggCol    in varchar2 --对应pivot函数的 聚合函数
                                        ,as_changeCol in varchar2 --源数据中，要转为列的字段名
                                        ,as_viewName  in varchar2 --结果输出的视图名，以后直接查询这个视图即可
                                         ) authid current_user is --赋予存储过程调用者权限
  ls_sql varchar2(4000);
  ls_in  varchar2(4000);
begin
  --拼接in的内容
  ls_sql := 'select listagg(''''''''||cols||'''''' "''||cols||''"'', '','')within group(order by rn) ' || 
              'from (select rownum rn, cols from (' || as_sql_cols || '))';
  execute immediate ls_sql
    into ls_in;
 
  --创建视图
  ls_sql := 'create or replace view ' || as_viewName ||' as ' ||
            'select * from (' || as_sql || ') ' ||
             'pivot (' || as_aggCol || ' for ' || as_changeCol || ' in (' || ls_in || '))';
  execute immediate ls_sql;
end p_RowsToCols;

---测试

--动态行转列
call p_RowsToCols('select keHu, shangPin, salesNum from salesList',
                  'select distinct shangPinId, shangPin cols from salesList order by shangPinId',
                  'max(salesNum)',
                  'shangPin',
                  'sales_RowsToCols');
 
select * from sales_RowsToCols;

```

