----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/04/2022 10:29:08 PM
-- Design Name: 
-- Module Name: Serializer - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Serializer is
    Generic(
        row_cnt : Integer := 5
    );
    Port (
        col_0 : in std_logic_vector(row_cnt - 1 downto 0);
        col_1 : in std_logic_vector(row_cnt - 1 downto 0);
        col_2 : in std_logic_vector(row_cnt - 1 downto 0);
        col_3 : in std_logic_vector(row_cnt - 1 downto 0);
        col_4 : in std_logic_vector(row_cnt - 1 downto 0);
        
        in_clk : in std_logic;
        rst : in std_logic;
        
        ser_0 : out std_logic;
        ser_1 : out std_logic;
        ser_2 : out std_logic;
        ser_3 : out std_logic;
        ser_4 : out std_logic;
        
        reg_clk : out std_logic;
        out_clk : out std_logic
    );
end Serializer;

architecture Behavioral of Serializer is
    type state_type is (s0, s1, s2);
    signal state   : state_type;
    
    signal shift_cnt : Integer := 0;
    signal out_clk_en : std_logic := '1';
begin

    out_clk <= in_clk;

    process(in_clk, rst) is
    begin
        if rst = '0' then
            state <= s0;
            ser_0 <= '0';
            ser_1 <= '0';
            ser_2 <= '0';
            ser_3 <= '0';
            ser_4 <= '0';
            reg_clk <= '0';
            out_clk_en <= '0';
            shift_cnt <= 0;
            
        elsif falling_edge(in_clk) then
            
            shift_cnt <= shift_cnt + 1;
            
            ser_0 <= col_0(shift_cnt);
            ser_1 <= col_1(shift_cnt);
            ser_2 <= col_2(shift_cnt);
            ser_3 <= col_3(shift_cnt);
            ser_4 <= col_4(shift_cnt);
            
            if shift_cnt = 0 then
                reg_clk <= '1';
            end if;
            
            if shift_cnt = 1 then
                reg_clk <= '0';
            end if;
            
            if shift_cnt = row_cnt - 1 then
                shift_cnt <= 0;
            end if;
        end if;
    end process;

end Behavioral;