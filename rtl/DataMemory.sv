/* verilator lint_off UNUSEDSIGNAL */

module DataMemory #(parameter REG_BITS=32) 
(
    input logic  [REG_BITS-1:0] U,
    input logic [REG_BITS-1:0] WD,
    input logic CLK, WE,
    output logic  [REG_BITS-1:0] RD
);

    logic [REG_BITS-1:0] mem [2 ** 10-1:0];

    initial begin
        $display("Read RAM");
        $readmemh("./mem/hex_ram.mem", mem); // load hex file
        //$readmemb("../mem/bin_ram.mem", mem); // load bin file

    end

    always_comb begin
        RD = mem[A];
    end

    always_ff @(posedge CLK) begin
       if (WE) begin
            mem[A] = WD;
       end
    end

endmodule

