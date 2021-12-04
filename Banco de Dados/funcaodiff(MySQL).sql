CREATE DEFINER=`root`@`localhost` FUNCTION `CalcDiff`(hi DATETIME, hf DATETIME) RETURNS int
    DETERMINISTIC
BEGIN
    declare diff integer; 
    set diff = TIMESTAMPDIFF(MINUTE,hi,hf);
    return(diff);
END