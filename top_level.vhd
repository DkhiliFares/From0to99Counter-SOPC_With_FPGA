library ieee;
use ieee.std_logic_1164.all;

entity TopLevel is
    port (
        CLOCK_50 : in  std_logic;
        RESET_N  : in  std_logic;

        -- 4 seven-segment outputs
        HEX0 : out std_logic_vector(6 downto 0);
        HEX1 : out std_logic_vector(6 downto 0);
        HEX2 : out std_logic_vector(6 downto 0);
        HEX3 : out std_logic_vector(6 downto 0)
    );
end entity TopLevel;


architecture rtl of TopLevel is

 component Processeur2 is
        port (
            clk_clk                                     : in  std_logic                    := 'X'; -- clk
            reset_reset_n                               : in  std_logic                    := 'X'; -- reset_n
            display7segment2_external_connection_export : out std_logic_vector(6 downto 0);        -- export
            display7segment3_external_connection_export : out std_logic_vector(6 downto 0);        -- export
            display7segment4_external_connection_export : out std_logic_vector(6 downto 0);        -- export
            display7segment1_external_connection_export : out std_logic_vector(6 downto 0)         -- export
        );
    end component Processeur2;

begin

    -- Instantiate Qsys system
    u0 : Processeur2
        port map (
            clk_clk       => CLOCK_50,
            reset_reset_n => RESET_N,

            -- IMPORTANT: match Qsys naming → real outputs
            display7segment1_external_connection_export => HEX0,
            display7segment2_external_connection_export => HEX1,
            display7segment3_external_connection_export => HEX2,
            display7segment4_external_connection_export => HEX3
        );

end architecture rtl;
