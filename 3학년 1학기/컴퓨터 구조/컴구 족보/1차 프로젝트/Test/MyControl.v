`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:24:49 07/31/2019 
// Design Name: 
// Module Name:    MyControl 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module MyControl(op,RegDst,Jump,Branch,MemtoReg,ALUOp,MemWrite,ALUSrc,RegWrite,PCToReg,ExtMode);
	input [5:0] op;                                  
	output reg [1:0] RegDst;
	output reg Jump,Branch,MemtoReg;                 
	output reg [3:0] ALUOp;                          
	output reg MemWrite,ALUSrc,RegWrite,PCToReg;
	output reg ExtMode;

	always@(op) begin
		if(op==6'b000000)begin   // R_TYPE
			ALUOp<=4'b0010;	//R_Type instruction
			RegDst<=2'b01;		//DesReg = rd
			ALUSrc<=1'b0;		//Get Read Data2 from RF
			RegWrite<=1'b1;    //Write enable
			MemtoReg<=1'b0;    //Send ALU result data to register
			MemWrite<=1'b0;    //Write disable
			Jump<=1'b0;    	//Jump disable
			Branch<=1'b0;    //Branch disable
			PCToReg<=1'b0;		//Get Write data from U11
			ExtMode<=1'bx; 	//Don't care of extension
		end
		else if(op==6'b000100) begin // beq
			ALUOp<=4'b0001;   //SUB instruction
			RegDst<=2'bxx;     //Don't care of Destination Register
			ALUSrc<=1'b0;     //Get Read Data2 from RF
			RegWrite<=1'b0;   //Write disable
			MemtoReg<=1'bx;   //Don't care of data
			MemWrite<=1'b0;   //Write disable
			Jump<=1'b0;       //Jump disable
			Branch<=1'b1;     //Branch enable
			PCToReg<=1'b0;		//Get Write data from U11
			ExtMode<=1'b1; 	//Sign extension
		end
		else if(op == 6'b000101) begin // bne
			RegDst <= 2'bxx;     //Don't care of Destination Register
			ALUOp <= 4'b0001;   //SUB instruction
			ALUSrc <= 1'b0;     //Get Read Data2 from RF
			RegWrite <= 1'b0;  //Write disable
			PCToReg <= 1'b0;		//Get Write data from U11
			MemtoReg <= 1'bx;   //Don't care of data
			MemWrite <= 1'b0;   //Write disable
			Branch <= 1'b1;     //Branch enable
			Jump <= 1'b0;	      //Jump disable
			ExtMode <= 1'b1; 		//Sign extension
		end
		else if(op==6'b001100) begin // andi
			ALUOp<=4'b0000;		//ADD instruction(due to the absence of AND)
			RegDst<=2'b00;   		//DesReg = rt
			ALUSrc<=1'b1;    		//Get extended immediate value
			RegWrite<=1'b1;  		//Write enable
			MemtoReg<=1'b0;    //Send ALU result data to register
			MemWrite<=1'b0;  		//Write disable
			Jump<=1'b0;      		//Jump disable
			Branch<=1'b0;    		//Branch disable
			PCToReg<=1'b0;			//Get Write data from U11
			ExtMode<=1'b0; 		//Zero extension
		end 
		else if(op==6'b000011) begin // jal
			ALUOp<=4'bxxxx;		//Don't care of ALU
			RegDst<=2'b10; 		//DesReg = $31
			ALUSrc<=1'bx;  		//Don't care of ALU
			RegWrite<=1'b1;		//Write enable
			MemtoReg<=1'bx;		//Don't care of data
			MemWrite<=1'b0;		//Write disable
			Jump<=1'b1;  			//Jump enable
			Branch<=1'bx;			//Don't care of Branch
			PCToReg<=1'b1;			//Get Write data from PC+4
			ExtMode<=1'bx; 		//Don't care of Extension
		end
		else if(op==6'b001110) begin // xori
			ALUOp<=4'b0011;		//XOR instruction
			RegDst<=2'b00; 		//DesReg = rt
         ALUSrc<=1'b1;  		//Get extended immediate value
         RegWrite<=1'b1;		//Write enable
         MemtoReg<=1'b0;		//Send ALU result data to register
         MemWrite<=1'b0;		//Write disable
         Jump<=1'b0;    		//Jump disable
         Branch<=1'b0; 			//Branch disable
			PCToReg<=1'b0;			//Get Write data from U11
			ExtMode<=1'b0; 		//Zero extension
      end
		else if(op==6'b001010) begin // slti 
			ALUOp<=4'b0100;		//SLT instruction
			RegDst<=2'b00; 		//DesReg = rt
         ALUSrc<=1'b1;    		//Get extended immediate value
         RegWrite<=1'b1;		//Write enable
         MemtoReg<=1'b0;		//Send ALU result data to register
         MemWrite<=1'b0;		//Write disable
         Jump<=1'b0;   			//Jump disable
         Branch<=1'b0; 			//Branch disable
 			PCToReg<=1'b0;			//Get Write data from U11
			ExtMode<=1'b1; 		//Sign extension
      end
		else begin				//Default
			ALUOp<=4'bx;   
			RegDst<=2'bxx; 
			ALUSrc<=1'bx;  
			RegWrite<=1'bx;
			MemtoReg<=1'bx;
			MemWrite<=1'bx;
			Jump<=1'bx;    
			Branch<=1'bx;  
			PCToReg<=1'bx;
			ExtMode<=1'bx; 
		end
	end
endmodule
