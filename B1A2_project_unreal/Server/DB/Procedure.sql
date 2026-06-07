CREATE PROCEDURE CheckLogin
    @InputId varchar(20)
AS
BEGIN
    SELECT user_id 
    FROM UserInfo 
    WHERE user_id = @InputId;
END