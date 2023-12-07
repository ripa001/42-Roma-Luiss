import { Type } from 'class-transformer';
import { IsEmail, IsNotEmpty, IsString, Length, Matches, MaxLength, MinLength, Validate, IsNumber, IsDate, IsOptional } from 'class-validator';



export class Chat {
	@IsNotEmpty()
	@IsString()
	content: string;

	@IsNotEmpty()
	@Type(() => Date)
	@IsDate()
	createdAt: Date;

	@IsNotEmpty()
	@IsNumber()
	senderID: number;

	@IsOptional()
	receiverID: number | null;

	@IsOptional()
	receiversID: number | null;
}
