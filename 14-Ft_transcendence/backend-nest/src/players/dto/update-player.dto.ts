import { PartialType } from '@nestjs/mapped-types';
import { CreatePlayerDto } from './create-player.dto';
import { ApiProperty } from '@nestjs/swagger';

export class UpdatePlayerDto {

	@ApiProperty()
	username?: string;
	@ApiProperty()
	avatar?: string;

	@ApiProperty()
	profileIntra?: string;
	@ApiProperty()
	twofaSecret?: string;
}
