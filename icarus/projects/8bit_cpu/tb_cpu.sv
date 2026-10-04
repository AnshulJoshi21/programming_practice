// GATE TESTS
module tb_gates;

  parameter int WIDTH = 1;

  logic nand_a;
  logic nand_b;
  logic nand_y;

  logic [WIDTH-1:0] a;
  logic [WIDTH-1:0] b;

  logic [WIDTH-1:0] not_y;
  logic [WIDTH-1:0] and_y;
  logic [WIDTH-1:0] or_y;
  logic [WIDTH-1:0] xor_y;

  nand_gate nand1(
    .a(nand_a),
    .b(nand_b),
    .y(nand_y)
  );

  not_gate #(.WIDTH(WIDTH)) not1(
    .a(a),
    .y(not_y)
  );

  and_gate #(.WIDTH(WIDTH)) and1(
    .a(a),
    .b(b),
    .y(and_y)
  );

  or_gate #(.WIDTH(WIDTH)) or1(
    .a(a),
    .b(b),
    .y(or_y)
  );

  xor_gate #(.WIDTH(WIDTH)) xor1(
    .a(a),
    .b(b),
    .y(xor_y)
  );

  initial begin
    nand_a=1'b0; nand_b=1'b0; a=1'b0; b=1'b0; #1;
    if (nand_y !== 1) $display("ERROR: nand(%b, %b) = %b", nand_a, nand_b, nand_y); 
    if (not_y !== 1) $display("ERROR: not(%b) = %b", a, not_y); 
    if (and_y !== 0) $display("ERROR: and(%b, %b) = %b", a, b, and_y); 
    if (or_y !== 0) $display("ERROR: or(%b, %b) = %b", a, b, or_y); 
    if (xor_y !== 0) $display("ERROR: xor(%b, %b) = %b", a, b, xor_y); 
  
    nand_a=1'b0; nand_b=1'b1; a=1'b0; b=1'b1; #1;
    if (nand_y !== 1) $display("ERROR: nand(%b, %b) = %b", nand_a, nand_b, nand_y); 
    if (not_y !== 1) $display("ERROR: not(%b) = %b", a, not_y); 
    if (and_y !== 0) $display("ERROR: and(%b, %b) = %b", a, b, and_y); 
    if (or_y !== 1) $display("ERROR: or(%b, %b) = %b", a, b, or_y); 
    if (xor_y !== 1) $display("ERROR: xor(%b, %b) = %b", a, b, xor_y); 
  
    nand_a=1'b1; nand_b=1'b0; a=1'b1; b=1'b0; #1;
    if (nand_y !== 1) $display("ERROR: nand(%b, %b) = %b", nand_a, nand_b, nand_y); 
    if (not_y !== 0) $display("ERROR: not(%b) = %b", a, not_y); 
    if (and_y !== 0) $display("ERROR: and(%b, %b) = %b", a, b, and_y); 
    if (or_y !== 1) $display("ERROR: or(%b, %b) = %b", a, b, or_y); 
    if (xor_y !== 1) $display("ERROR: xor(%b, %b) = %b", a, b, xor_y); 
  
    nand_a=1'b1; nand_b=1'b1; a=1'b1; b=1'b1; #1;
    if (nand_y !== 0) $display("ERROR: nand(%b, %b) = %b", nand_a, nand_b, nand_y); 
    if (not_y !== 0) $display("ERROR: not(%b) = %b", a, not_y); 
    if (and_y !== 1) $display("ERROR: and(%b, %b) = %b", a, b, and_y); 
    if (or_y !== 1) $display("ERROR: or(%b, %b) = %b", a, b, or_y); 
    if (xor_y !== 0) $display("ERROR: xor(%b, %b) = %b", a, b, xor_y); 
  
  
    $display("All gate tests passed");
  end
  
endmodule

// ADDER TESTS
module tb_adders;

  parameter int WIDTH = 1;

  logic ha_a;
  logic ha_b;
  logic ha_sum;
  logic ha_cout;
  

  logic [WIDTH-1:0] fa_a;
  logic [WIDTH-1:0] fa_b;
  logic fa_cin;
  logic [WIDTH-1:0] fa_sum;
  logic fa_cout;

  half_adder ha1(
    .a(ha_a),
    .b(ha_b),
    .sum(ha_sum),
    .cout(ha_cout)
  );

  full_adder #(.WIDTH(WIDTH)) fa1(
    .a(fa_a),
    .b(fa_b),
    .cin(fa_cin),
    .sum(fa_sum),
    .cout(fa_cout)
  );

  initial begin

    // half adder test
    ha_a=1'b0; ha_b=1'b0; #1;
    if (ha_sum !== 1'b0 || ha_cout != 1'b0) $display("ERROR: half_adder(%b, %b) = sum=%b, cout=%b", ha_a, ha_b, ha_sum, ha_cout); 

    ha_a=1'b0; ha_b=1'b1; #1;
    if (ha_sum !== 1'b1 || ha_cout != 1'b0) $display("ERROR: half_adder(%b, %b) = sum=%b, cout=%b", ha_a, ha_b, ha_sum, ha_cout); 

    ha_a=1'b1; ha_b=1'b0; #1;
    if (ha_sum !== 1'b1 || ha_cout != 1'b0) $display("ERROR: half_adder(%b, %b) = sum=%b, cout=%b", ha_a, ha_b, ha_sum, ha_cout); 

    ha_a=1'b1; ha_b=1'b1; #1;
    if (ha_sum !== 1'b0 || ha_cout != 1'b1) $display("ERROR: half_adder(%b, %b) = sum=%b, cout=%b", ha_a, ha_b, ha_sum, ha_cout); 

    // full adder test
    fa_a=1'b0; fa_b=1'b0; fa_cin=1'b0; #1;
    if (fa_sum !== 1'b0 || fa_cout !== 1'b0) $display("ERROR: full_adder(%b, %b, %b) = sum=%b, cout=%b", fa_a, fa_b, fa_cin, fa_sum, fa_cout); 
  
    fa_a=1'b0; fa_b=1'b0; fa_cin=1'b1; #1;
    if (fa_sum !== 1'b1 || fa_cout !== 1'b0) $display("ERROR: full_adder(%b, %b, %b) = sum=%b, cout=%b", fa_a, fa_b, fa_cin, fa_sum, fa_cout); 
  
    fa_a=1'b0; fa_b=1'b1; fa_cin=1'b0; #1;
    if (fa_sum !== 1'b1 || fa_cout !== 1'b0) $display("ERROR: full_adder(%b, %b, %b) = sum=%b, cout=%b", fa_a, fa_b, fa_cin, fa_sum, fa_cout); 
  
    fa_a=1'b0; fa_b=1'b1; fa_cin=1'b1; #1;
    if (fa_sum !== 1'b0 || fa_cout !== 1'b1) $display("ERROR: full_adder(%b, %b, %b) = sum=%b, cout=%b", fa_a, fa_b, fa_cin, fa_sum, fa_cout); 
  
    fa_a=1'b1; fa_b=1'b0; fa_cin=1'b0; #1;
    if (fa_sum !== 1'b1 || fa_cout !== 1'b0) $display("ERROR: full_adder(%b, %b, %b) = sum=%b, cout=%b", fa_a, fa_b, fa_cin, fa_sum, fa_cout); 
  
    fa_a=1'b1; fa_b=1'b0; fa_cin=1'b1; #1;
    if (fa_sum !== 1'b0 || fa_cout !== 1'b1) $display("ERROR: full_adder(%b, %b, %b) = sum=%b, cout=%b", fa_a, fa_b, fa_cin, fa_sum, fa_cout); 
  
    fa_a=1'b1; fa_b=1'b1; fa_cin=1'b0; #1;
    if (fa_sum !== 1'b0 || fa_cout !== 1'b1) $display("ERROR: full_adder(%b, %b, %b) = sum=%b, cout=%b", fa_a, fa_b, fa_cin, fa_sum, fa_cout); 
  
    fa_a=1'b1; fa_b=1'b1; fa_cin=1'b1; #1;
    if (fa_sum !== 1'b1 || fa_cout !== 1'b1) $display("ERROR: full_adder(%b, %b, %b) = sum=%b, cout=%b", fa_a, fa_b, fa_cin, fa_sum, fa_cout); 

    $display("All adder tests passed");
  end
  
endmodule

// MUX TESTS
module tb_muxes;

  logic [2:0] sel;
  logic [7:0] data;
  logic m2_y;
  logic m4_y;
  logic m8_y;

  mux_2x1 m2(
    .sel(sel[0]),
    .data(data[1:0]),
    .y(m2_y)
  );

  mux_4x1 m4(
    .sel(sel[1:0]),
    .data(data[3:0]),
    .y(m4_y)
  );

  mux_8x1 m8(
    .sel(sel),
    .data(data),
    .y(m8_y)
  );
  
  integer s;
  integer d;
  
  initial begin

    // mux 2:1 test
    for (s = 0; s < 2; s++) begin
      for (d = 0; d < 4; d++) begin
        sel = s;
        data = d;
        #1;

        if (m2_y !== data[sel[0]]) $display("ERROR: MUX 2:1 = sel(%b), data(%b), y(%b), expected(%b)", sel, data, m2_y, data[sel]);

      end
    end

    // mux 4:1 test
    for (s = 0; s < 4; s++) begin
      for (d = 0; d < 16; d++) begin
        sel = s;
        data = d;
        #1;

        if (m4_y !== data[sel[1:0]]) $display("ERROR: MUX 4:1 = sel(%b), data(%b), y(%b), expected(%b)", sel, data, m4_y, data[sel]);
      
      end
    end
  
    // mux 8:1 test
    for (s = 0; s < 8; s++) begin
      for (d = 0; d < 256; d++) begin
        sel = s;
        data = d;
        #1;

        if (m8_y !== data[sel]) $display("ERROR: MUX 8:1 = sel(%b), data(%b), y(%b), expected(%b)", sel, data, m4_y, data[sel]);

      end
    end
  
    $display("All mux tests passed");
  end
  
endmodule

// DMUX TESTS
module tb_dmuxes;

  logic [2:0] sel;
  logic data;
  logic [1:0] dm2_y;
  logic [3:0] dm4_y;
  logic [7:0] dm8_y;

  dmux_1x2 dm2(
    .sel(sel[0]),
    .data(data),
    .y(dm2_y)
  );

  dmux_1x4 dm4(
    .sel(sel[1:0]),
    .data(data),
    .y(dm4_y)
  );

  dmux_1x8 dm8(
    .sel(sel),
    .data(data),
    .y(dm8_y)
  );

  integer s;
  integer d;
  
  initial begin

    for (d = 0; d < 2; d++) begin
      data = d;

      // 1:2 test
      for (s = 0; s < 2; s++) begin
        sel = s;
        #1;

        if (dm2_y !== ((data) ? (2'b01 << sel) : 2'b00)) $display("ERROR: DMUX 2:1 = sel(%b), data(%b), y(%b)", sel, data, dm2_y);

      end

      // 1:4 test
      for (s = 0; s < 4; s++) begin
        sel = s;
        #1;

        if (dm4_y !== ((data) ? (4'b0001 << sel) : 4'b0000)) $display("ERROR: DMUX 4:1 = sel(%b), data(%b), y(%b)", sel, data, dm4_y);

      end

      // 1:8 test
      for (s = 0; s < 8; s++) begin
        sel = s;
        #1;

        if (dm8_y !== ((data) ? (8'b00000001 << sel) : 8'b00000000)) $display("ERROR: DMUX 8:1 = sel(%b), data(%b), y(%b)", sel, data, dm8_y);

      end
    
    end
  
    $display("All dmux tests passed");
  end

endmodule

module tb_basic_operations;

  parameter int WIDTH = 8;

  logic [WIDTH-1:0] a;
  logic [WIDTH-1:0] b;

  logic [WIDTH-1:0] add_sum;
  logic add_cout;

  logic [WIDTH-1:0] sub_sum;
  logic sub_cout;

  logic [WIDTH-1:0] shl_y;
  logic shl_cout;

  logic [WIDTH-1:0] shr_y;
  logic shr_cout;

  add #(.WIDTH(WIDTH)) add1(
    .a(a),
    .b(b),
    .sum(add_sum),
    .cout(add_cout)
  );

  sub #(.WIDTH(WIDTH)) sub1(
    .a(a),
    .b(b),
    .sum(sub_sum),
    .cout(sub_cout)
  );

  shl #(.WIDTH(WIDTH)) shl1(
    .a(a),
    .y(shl_y),
    .cout(shl_cout)
  );

  shr #(.WIDTH(WIDTH)) shr1(
    .a(a),
    .y(shr_y),
    .cout(shr_cout)
  );

  initial begin

    a=8'b00000101; b=8'b00000011; #1;
    if (add_sum !== 8'b00001000 || add_cout !== 1'b0) $display("ERROR add(%b, %b) = sum(%b), carry(%b)", a, b, add_sum, add_cout);
    if (sub_sum !== 8'b00000010 || sub_cout !== 1'b1) $display("ERROR sub(%b, %b) = sum(%b), carry(%b)", a, b, sub_sum, sub_cout);
    if (shl_y !== 8'b00001010 || shl_cout !== 1'b0) $display("ERROR shl(%b, %b) = y(%b), carry(%b)", a, b, shl_y, shl_cout);
    if (shr_y !== 8'b00000010 || shr_cout !== 1'b1) $display("ERROR shr(%b, %b) = y(%b), carry(%b)", a, b, shr_y, shr_cout);

    // Test 2
    a = 8'b11111111; b = 8'b00000001; #1;
    if (add_sum !== 8'b00000000 || add_cout !== 1'b1) $display("ERROR add(%b, %b) = sum(%b), carry(%b)", a, b, add_sum, add_cout);
    if (sub_sum !== 8'b11111110 || sub_cout !== 1'b1) $display("ERROR sub(%b, %b) = sum(%b), carry(%b)", a, b, sub_sum, sub_cout);
    if (shl_y !== 8'b11111110 || shl_cout !== 1'b1) $display("ERROR shl(%b, %b) = y(%b), carry(%b)", a, b, shl_y, shl_cout);
    if (shr_y !== 8'b01111111 || shr_cout !== 1'b1) $display("ERROR shr(%b, %b) = y(%b), carry(%b)", a, b, shr_y, shr_cout);

    // Test 3
    a = 8'b00000000; b = 8'b00000000; #1;
    if (add_sum !== 8'b00000000 || add_cout !== 1'b0) $display("ERROR add(%b, %b) = sum(%b), carry(%b)", a, b, add_sum, add_cout);
    if (sub_sum !== 8'b00000000 || sub_cout !== 1'b1) $display("ERROR sub(%b, %b) = sum(%b), carry(%b)", a, b, sub_sum, sub_cout);
    if (shl_y !== 8'b00000000 || shl_cout !== 1'b0) $display("ERROR shl(%b, %b) = y(%b), carry(%b)", a, b, shl_y, shl_cout);
    if (shr_y !== 8'b00000000 || shr_cout !== 1'b0) $display("ERROR shr(%b, %b) = y(%b), carry(%b)", a, b, shr_y, shr_cout);

    // Test 4
    a = 8'b10000000; b = 8'b00000001; #1;
    if (add_sum !== 8'b10000001 || add_cout !== 1'b0) $display("ERROR add(%b, %b) = sum(%b), carry(%b)", a, b, add_sum, add_cout);
    if (sub_sum !== 8'b01111111 || sub_cout !== 1'b1) $display("ERROR sub(%b, %b) = sum(%b), carry(%b)", a, b, sub_sum, sub_cout);
    if (shl_y !== 8'b00000000 || shl_cout !== 1'b1) $display("ERROR shl(%b, %b) = y(%b), carry(%b)", a, b, shl_y, shl_cout);
    if (shr_y !== 8'b01000000 || shr_cout !== 1'b0) $display("ERROR shr(%b, %b) = y(%b), carry(%b)", a, b, shr_y, shr_cout);

    // Test 5
    a = 8'b01010101; b = 8'b00110011; #1;
    if (add_sum !== 8'b10001000 || add_cout !== 1'b0) $display("ERROR add(%b, %b) = sum(%b), carry(%b)", a, b, add_sum, add_cout);
    if (sub_sum !== 8'b00100010 || sub_cout !== 1'b1) $display("ERROR sub(%b, %b) = sum(%b), carry(%b)", a, b, sub_sum, sub_cout);
    if (shl_y !== 8'b10101010 || shl_cout !== 1'b0) $display("ERROR shl(%b, %b) = y(%b), carry(%b)", a, b, shl_y, shl_cout);
    if (shr_y !== 8'b00101010 || shr_cout !== 1'b1) $display("ERROR shr(%b, %b) = y(%b), carry(%b)", a, b, shr_y, shr_cout);

    // Test 6: subtraction with borrow
    a = 8'b00000011; b = 8'b00000101; #1;
    if (add_sum !== 8'b00001000 || add_cout !== 1'b0) $display("ERROR add(%b, %b) = sum(%b), carry(%b)", a, b, add_sum, add_cout);
    if (sub_sum !== 8'b11111110 || sub_cout !== 1'b0) $display("ERROR sub(%b, %b) = sum(%b), carry(%b)", a, b, sub_sum, sub_cout);
    if (shl_y !== 8'b00000110 || shl_cout !== 1'b0) $display("ERROR shl(%b) = y(%b), carry(%b)", a, shl_y, shl_cout);
    if (shr_y !== 8'b00000001 || shr_cout !== 1'b1) $display("ERROR shr(%b) = y(%b), carry(%b)", a, shr_y, shr_cout);
  
    $display("All basic operation tests passed");
  end

endmodule

// ALU8
module tb_alu8;

  logic [2:0] opcode;
  logic [7:0] a;
  logic [7:0] b;
  logic [7:0] y;
  logic carry;
  logic sign;
  logic zero;
  logic overflow;

  alu8 u_alu (
    .opcode(opcode),
    .a(a),
    .b(b),
    .y(y),
    .carry(carry),
    .sign(sign),
    .zero(zero),
    .overflow(overflow)
  );

  // ------------------------------------------------------------
  // Test helper
  // ------------------------------------------------------------
  task automatic check(
    input logic [2:0] op,
    input logic [7:0] av,
    input logic [7:0] bv,
    input logic [7:0] expected_y,
    input logic expected_carry,
    input logic expected_sign,
    input logic expected_zero,
    input logic expected_overflow
  );

    opcode = op;
    a      = av;
    b      = bv;

    #1;

    if (y !== expected_y ||
        carry !== expected_carry ||
        sign !== expected_sign ||
        zero !== expected_zero ||
        overflow !== expected_overflow) begin

      $display(
        "FAIL: op=%b a=%h b=%h got: y=%h C=%b S=%b Z=%b V=%b expected: y=%h C=%b S=%b Z=%b V=%b",
        op, av, bv,
        y, carry, sign, zero, overflow,
        expected_y, expected_carry, expected_sign,
        expected_zero, expected_overflow
      );

      $fatal;
    end
  endtask


  initial begin

    // ============================================================
    // ADD (000)
    // ============================================================

    // 5 + 3 = 8
    check(3'b000, 8'h05, 8'h03,
          8'h08, 1'b0, 1'b0, 1'b0, 1'b0);

    // 0 + 0 = 0
    check(3'b000, 8'h00, 8'h00,
          8'h00, 1'b0, 1'b0, 1'b1, 1'b0);

    // 255 + 1 = 0 with carry
    check(3'b000, 8'hFF, 8'h01,
          8'h00, 1'b1, 1'b0, 1'b1, 1'b0);

    // Signed overflow: 127 + 1 = -128
    check(3'b000, 8'h7F, 8'h01,
          8'h80, 1'b0, 1'b1, 1'b0, 1'b1);

    // Signed overflow: -128 + -1 = 127
    check(3'b000, 8'h80, 8'hFF,
          8'h7F, 1'b1, 1'b0, 1'b0, 1'b1);


    // ============================================================
    // SUB (001)
    // ============================================================

    // 5 - 3 = 2
    check(3'b001, 8'h05, 8'h03,
          8'h02, 1'b0, 1'b0, 1'b0, 1'b0);

    // 3 - 3 = 0
    check(3'b001, 8'h03, 8'h03,
          8'h00, 1'b0, 1'b0, 1'b1, 1'b0);

    // 0 - 1 = FF
    check(3'b001, 8'h00, 8'h01,
          8'hFF, 1'b1, 1'b1, 1'b0, 1'b0);

    // Signed overflow: 127 - (-1) = -128
    check(3'b001, 8'h7F, 8'hFF,
          8'h80, 1'b1, 1'b1, 1'b0, 1'b1);

    // Signed overflow: -128 - 1 = 127
    check(3'b001, 8'h80, 8'h01,
          8'h7F, 1'b0, 1'b0, 1'b0, 1'b1);


    // ============================================================
    // AND (010)
    // ============================================================

    check(3'b010, 8'hF0, 8'h0F,
          8'h00, 1'b0, 1'b0, 1'b1, 1'b0);

    check(3'b010, 8'hAA, 8'hFF,
          8'hAA, 1'b0, 1'b1, 1'b0, 1'b0);


    // ============================================================
    // OR (011)
    // ============================================================

    check(3'b011, 8'hF0, 8'h0F,
          8'hFF, 1'b0, 1'b1, 1'b0, 1'b0);

    check(3'b011, 8'h00, 8'h00,
          8'h00, 1'b0, 1'b0, 1'b1, 1'b0);


    // ============================================================
    // XOR (100)
    // ============================================================

    check(3'b100, 8'hAA, 8'hAA,
          8'h00, 1'b0, 1'b0, 1'b1, 1'b0);

    check(3'b100, 8'hAA, 8'h55,
          8'hFF, 1'b0, 1'b1, 1'b0, 1'b0);


    // ============================================================
    // NOT (101)
    // ============================================================

    check(3'b101, 8'h00, 8'h00,
          8'hFF, 1'b0, 1'b1, 1'b0, 1'b0);

    check(3'b101, 8'hFF, 8'h00,
          8'h00, 1'b0, 1'b0, 1'b1, 1'b0);


    // ============================================================
    // SHL (110)
    // ============================================================

    // 00000001 << 1 = 00000010
    check(3'b110, 8'h01, 8'h00,
          8'h02, 1'b0, 1'b0, 1'b0, 1'b0);

    // 10000000 << 1 = 00000000, carry = 1
    check(3'b110, 8'h80, 8'h00,
          8'h00, 1'b1, 1'b0, 1'b1, 1'b0);

    // 11111111 << 1 = 11111110, carry = 1
    check(3'b110, 8'hFF, 8'h00,
          8'hFE, 1'b1, 1'b1, 1'b0, 1'b0);


    // ============================================================
    // SHR (111)
    // ============================================================

    // 00000010 >> 1 = 00000001
    check(3'b111, 8'h02, 8'h00,
          8'h01, 1'b0, 1'b0, 1'b0, 1'b0);

    // 00000001 >> 1 = 00000000, carry = 1
    check(3'b111, 8'h01, 8'h00,
          8'h00, 1'b1, 1'b0, 1'b1, 1'b0);

    // 10000000 >> 1 = 01000000
    check(3'b111, 8'h80, 8'h00,
          8'h40, 1'b0, 1'b0, 1'b0, 1'b0);


    $display("All alu8 tests passed");
    $finish;

  end

endmodule

module all_tests;
  tb_gates gates();
  tb_adders adders();
  tb_muxes muxes();
  tb_dmuxes dmuxes();
  tb_basic_operations basic_operations();
  tb_alu8 alu8();

endmodule

