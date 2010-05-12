DROP AGGREGATE join(text, text) CASCADE;
DROP FUNCTION cut_back(text) CASCADE;
DROP FUNCTION qq(text, text, text) CASCADE;
CREATE FUNCTION qq(text, text, text)
RETURNS text
LANGUAGE 'SQL'
AS '
   SELECT $1 || $3 || $2;
';

CREATE FUNCTION cut_back(text)
RETURNS text
LANGUAGE 'SQL'
AS '
   SELECT trim(both ''_'' from $1);
';


CREATE AGGREGATE join ( text, text ) (
    SFUNC = qq,
    STYPE = text,
		INITCOND = '',
    FINALFUNC = cut_back
);
