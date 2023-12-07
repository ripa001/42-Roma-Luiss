import { PartialType } from '@nestjs/mapped-types';
import { CreateChatDto } from './create-chat.dto';
import { IsNumber, IsNotEmpty } from 'class-validator';

export class UpdateChatDto extends PartialType(CreateChatDto) {
  @IsNotEmpty()
  @IsNumber()
  id: number;
}
