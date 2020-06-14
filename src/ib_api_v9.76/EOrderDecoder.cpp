/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"
#include "EOrderDecoder.h"

#include <string.h>
#include <cstdlib>
#include <sstream>
#include <assert.h>
#include <string>
#include <bitset>


EOrderDecoder::EOrderDecoder(Contract *contract, Order *order, OrderState *orderState, int version, int serverVersion) {
	m_contract = contract;
	m_order = order;
	m_orderState = orderState;
	m_version = version;
	m_serverVersion = serverVersion;
}

char* EOrderDecoder::decodeOrderId(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->orderId);
	return nullptr;
}

char* EOrderDecoder::decodeContract(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_contract->conId);
	DECODE_FIELD( m_contract->symbol);
	DECODE_FIELD( m_contract->secType);
	DECODE_FIELD( m_contract->lastTradeDateOrContractMonth);
	DECODE_FIELD( m_contract->strike);
	DECODE_FIELD( m_contract->right);
	if (m_version >= 32) {
		DECODE_FIELD( m_contract->multiplier);
	}
	DECODE_FIELD( m_contract->exchange);
	DECODE_FIELD( m_contract->currency);
	DECODE_FIELD( m_contract->localSymbol); // ver 2 field
	if (m_version >= 32) {
		DECODE_FIELD( m_contract->tradingClass);
	}
	return nullptr;
}

char* EOrderDecoder::decodeAction(const char*& ptr, const char* endPtr) {
	// read order fields
	DECODE_FIELD( m_order->action);
	return nullptr;
}

char* EOrderDecoder::decodeTotalQuantity(const char*& ptr, const char* endPtr) {
	if (m_serverVersion >= MIN_SERVER_VER_FRACTIONAL_POSITIONS)	{
		DECODE_FIELD( m_order->totalQuantity);
	} else {
		long lTotalQuantity;
		DECODE_FIELD(lTotalQuantity);
		m_order->totalQuantity = lTotalQuantity;
	}
	return nullptr;
}

char* EOrderDecoder::decodeOrderType(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->orderType);
	return nullptr;
}

char* EOrderDecoder::decodeLmtPrice(const char*& ptr, const char* endPtr) {
	if (m_version < 29) { 
		DECODE_FIELD( m_order->lmtPrice);
	} else {
		DECODE_FIELD_MAX( m_order->lmtPrice);
	}
	return nullptr;
}

char* EOrderDecoder::decodeAuxPrice(const char*& ptr, const char* endPtr) {
	if (m_version < 30) { 
		DECODE_FIELD( m_order->auxPrice);
	} else {
		DECODE_FIELD_MAX( m_order->auxPrice);
	}
	return nullptr;
}

char* EOrderDecoder::decodeTIF(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->tif);
	return nullptr;
}

char* EOrderDecoder::decodeOcaGroup(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->ocaGroup);
	return nullptr;
}

char* EOrderDecoder::decodeAccount(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->account);
	return nullptr;
}

char* EOrderDecoder::decodeOpenClose(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->openClose);
	return nullptr;
}

char* EOrderDecoder::decodeOrigin(const char*& ptr, const char* endPtr) {
	int orderOriginInt;
	DECODE_FIELD( orderOriginInt);
	m_order->origin = (Origin)orderOriginInt;
	return nullptr;
}

char* EOrderDecoder::decodeOrderRef(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->orderRef);
	return nullptr;
}

char* EOrderDecoder::decodeClientId(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->clientId);
	return nullptr;
}

char* EOrderDecoder::decodePermId(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->permId);
	return nullptr;
}

char* EOrderDecoder::decodeOutsideRth(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->outsideRth);
	return nullptr;
}

char* EOrderDecoder::decodeHidden(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->hidden);
	return nullptr;
}

char* EOrderDecoder::decodeDiscretionaryAmount(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->discretionaryAmt);
	return nullptr;
}

char* EOrderDecoder::decodeGoodAfterTime(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->goodAfterTime);
	return nullptr;
}

char* EOrderDecoder::skipSharesAllocation(const char*& ptr, const char* endPtr) {
	std::string sharesAllocation;
	DECODE_FIELD( sharesAllocation);
	return nullptr;
}

char* EOrderDecoder::decodeFAParams(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->faGroup);
	DECODE_FIELD( m_order->faMethod);
	DECODE_FIELD( m_order->faPercentage);
	DECODE_FIELD( m_order->faProfile);
	return nullptr;
}

char* EOrderDecoder::decodeModelCode(const char*& ptr, const char* endPtr) {
	if( m_serverVersion >= MIN_SERVER_VER_MODELS_SUPPORT ) {
		DECODE_FIELD( m_order->modelCode);
	}
	return nullptr;
}

char* EOrderDecoder::decodeGoodTillDate(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->goodTillDate);
	return nullptr;
}

char* EOrderDecoder::decodeRule80A(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->rule80A);
	return nullptr;
}

char* EOrderDecoder::decodePercentOffset(const char*& ptr, const char* endPtr) {
	DECODE_FIELD_MAX( m_order->percentOffset);
	return nullptr;
}

char* EOrderDecoder::decodeSettlingFirm(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->settlingFirm);
	return nullptr;
}

char* EOrderDecoder::decodeShortSaleParams(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->shortSaleSlot);
	DECODE_FIELD( m_order->designatedLocation);
	if( m_serverVersion == MIN_SERVER_VER_SSHORTX_OLD){
		int exemptCode;
		DECODE_FIELD( exemptCode);
	}
	else if( m_version >= 23){
		DECODE_FIELD( m_order->exemptCode);
	}
	return nullptr;
}

char* EOrderDecoder::decodeAuctionStrategy(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->auctionStrategy);
	return nullptr;
}

char* EOrderDecoder::decodeBoxOrderParams(const char*& ptr, const char* endPtr) {
	DECODE_FIELD_MAX( m_order->startingPrice);
	DECODE_FIELD_MAX( m_order->stockRefPrice);
	DECODE_FIELD_MAX( m_order->delta);
	return nullptr;
}

char* EOrderDecoder::decodePegToStkOrVolOrderParams(const char*& ptr, const char* endPtr) {
	DECODE_FIELD_MAX( m_order->stockRangeLower);
	DECODE_FIELD_MAX( m_order->stockRangeUpper);
	return nullptr;
}

char* EOrderDecoder::decodeDisplaySize(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->displaySize);
	return nullptr;
}

char* EOrderDecoder::decodeBlockOrder(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->blockOrder);
	return nullptr;
}

char* EOrderDecoder::decodeSweepToFill(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->sweepToFill);
	return nullptr;
}

char* EOrderDecoder::decodeAllOrNone(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->allOrNone);
	return nullptr;
}

char* EOrderDecoder::decodeMinQty(const char*& ptr, const char* endPtr) {
	DECODE_FIELD_MAX( m_order->minQty);
	return nullptr;
}

char* EOrderDecoder::decodeOcaType(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->ocaType);
	return nullptr;
}

char* EOrderDecoder::decodeETradeOnly(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->eTradeOnly);
	return nullptr;
}

char* EOrderDecoder::decodeFirmQuoteOnly(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->firmQuoteOnly);
	return nullptr;
}

char* EOrderDecoder::decodeNbboPriceCap(const char*& ptr, const char* endPtr) {
	DECODE_FIELD_MAX(m_order->nbboPriceCap);
	return nullptr;
}

char* EOrderDecoder::decodeParentId(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->parentId);
	return nullptr;
}

char* EOrderDecoder::decodeTriggerMethod(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->triggerMethod);
	return nullptr;
}

char* EOrderDecoder::decodeVolOrderParams(const char*& ptr, const char* endPtr, bool decodeOpenOrderAttribs) {
	DECODE_FIELD_MAX( m_order->volatility);
	DECODE_FIELD( m_order->volatilityType);
	DECODE_FIELD( m_order->deltaNeutralOrderType);
	DECODE_FIELD_MAX( m_order->deltaNeutralAuxPrice);

	if (m_version >= 27 && !m_order->deltaNeutralOrderType.empty()) {
		DECODE_FIELD( m_order->deltaNeutralConId);
		if (decodeOpenOrderAttribs) {
			DECODE_FIELD( m_order->deltaNeutralSettlingFirm);
			DECODE_FIELD( m_order->deltaNeutralClearingAccount);
			DECODE_FIELD( m_order->deltaNeutralClearingIntent);
		}
	}

	if (m_version >= 31 && !m_order->deltaNeutralOrderType.empty()) {
        if (decodeOpenOrderAttribs) {
			DECODE_FIELD( m_order->deltaNeutralOpenClose);
		}
		DECODE_FIELD( m_order->deltaNeutralShortSale);
		DECODE_FIELD( m_order->deltaNeutralShortSaleSlot);
		DECODE_FIELD( m_order->deltaNeutralDesignatedLocation);
	}

	DECODE_FIELD( m_order->continuousUpdate);
	DECODE_FIELD( m_order->referencePriceType);
	return nullptr;
}

char* EOrderDecoder::decodeTrailParams(const char*& ptr, const char* endPtr) {
	DECODE_FIELD_MAX( m_order->trailStopPrice);

	if (m_version >= 30) {
		DECODE_FIELD_MAX( m_order->trailingPercent);
	}
	return nullptr;
}

char* EOrderDecoder::decodeBasisPoints(const char*& ptr, const char* endPtr) {
	DECODE_FIELD_MAX( m_order->basisPoints);
	DECODE_FIELD_MAX( m_order->basisPointsType);
	return nullptr;
}

char* EOrderDecoder::decodeComboLegs(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_contract->comboLegsDescrip);

	if (m_version >= 29) {
		int comboLegsCount = 0;
		DECODE_FIELD( comboLegsCount);

		if (comboLegsCount > 0) {
			Contract::ComboLegListSPtr comboLegs( new Contract::ComboLegList);
			comboLegs->reserve( comboLegsCount);
			for (int i = 0; i < comboLegsCount; ++i) {
				ComboLegSPtr comboLeg( new ComboLeg());
				DECODE_FIELD( comboLeg->conId);
				DECODE_FIELD( comboLeg->ratio);
				DECODE_FIELD( comboLeg->action);
				DECODE_FIELD( comboLeg->exchange);
				DECODE_FIELD( comboLeg->openClose);
				DECODE_FIELD( comboLeg->shortSaleSlot);
				DECODE_FIELD( comboLeg->designatedLocation);
				DECODE_FIELD( comboLeg->exemptCode);

				comboLegs->push_back( comboLeg);
			}
			m_contract->comboLegs = comboLegs;
		}

		int orderComboLegsCount = 0;
		DECODE_FIELD( orderComboLegsCount);
		if (orderComboLegsCount > 0) {
			Order::OrderComboLegListSPtr orderComboLegs( new Order::OrderComboLegList);
			orderComboLegs->reserve( orderComboLegsCount);
			for (int i = 0; i < orderComboLegsCount; ++i) {
				OrderComboLegSPtr orderComboLeg( new OrderComboLeg());
				DECODE_FIELD_MAX( orderComboLeg->price);

				orderComboLegs->push_back( orderComboLeg);
			}
			m_order->orderComboLegs = orderComboLegs;
		}
	}
	return nullptr;
}

char* EOrderDecoder::decodeSmartComboRoutingParams(const char*& ptr, const char* endPtr) {
	if (m_version >= 26) {
		int smartComboRoutingParamsCount = 0;
		DECODE_FIELD( smartComboRoutingParamsCount);
		if( smartComboRoutingParamsCount > 0) {
			TagValueListSPtr smartComboRoutingParams( new TagValueList);
			smartComboRoutingParams->reserve( smartComboRoutingParamsCount);
			for( int i = 0; i < smartComboRoutingParamsCount; ++i) {
				TagValueSPtr tagValue( new TagValue());
				DECODE_FIELD( tagValue->tag);
				DECODE_FIELD( tagValue->value);
				smartComboRoutingParams->push_back( tagValue);
			}
			m_order->smartComboRoutingParams = smartComboRoutingParams;
		}
	}
	return nullptr;
}

char* EOrderDecoder::decodeScaleOrderParams(const char*& ptr, const char* endPtr) {
	if( m_version >= 20) {
		DECODE_FIELD_MAX( m_order->scaleInitLevelSize);
		DECODE_FIELD_MAX( m_order->scaleSubsLevelSize);
	}
	else {
		int notSuppScaleNumComponents = 0;
		DECODE_FIELD_MAX( notSuppScaleNumComponents);
		DECODE_FIELD_MAX( m_order->scaleInitLevelSize);
	}
	DECODE_FIELD_MAX( m_order->scalePriceIncrement);

	if (m_version >= 28 && m_order->scalePriceIncrement > 0.0 && m_order->scalePriceIncrement != UNSET_DOUBLE) {
		DECODE_FIELD_MAX( m_order->scalePriceAdjustValue);
		DECODE_FIELD_MAX( m_order->scalePriceAdjustInterval);
		DECODE_FIELD_MAX( m_order->scaleProfitOffset);
		DECODE_FIELD( m_order->scaleAutoReset);
		DECODE_FIELD_MAX( m_order->scaleInitPosition);
		DECODE_FIELD_MAX( m_order->scaleInitFillQty);
		DECODE_FIELD( m_order->scaleRandomPercent);
	}
	return nullptr;
}

char* EOrderDecoder::decodeHedgeParams(const char*& ptr, const char* endPtr) {
	if( m_version >= 24) {
		DECODE_FIELD( m_order->hedgeType);
		if( !m_order->hedgeType.empty()) {
			DECODE_FIELD( m_order->hedgeParam);
		}
	}
	return nullptr;
}

char* EOrderDecoder::decodeOptOutSmartRouting(const char*& ptr, const char* endPtr) {
	if( m_version >= 25) {
		DECODE_FIELD( m_order->optOutSmartRouting);
	}
	return nullptr;
}

char* EOrderDecoder::decodeClearingParams(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->clearingAccount);
	DECODE_FIELD( m_order->clearingIntent);
	return nullptr;
}

char* EOrderDecoder::decodeNotHeld(const char*& ptr, const char* endPtr) {
	if( m_version >= 22) {
		DECODE_FIELD( m_order->notHeld);
	}
	return nullptr;
}

char* EOrderDecoder::decodeDeltaNeutral(const char*& ptr, const char* endPtr) {
	DeltaNeutralContract deltaNeutralContract;
	if( m_version >= 20) {
		bool deltaNeutralContractPresent = false;
		DECODE_FIELD(deltaNeutralContractPresent);
		if( deltaNeutralContractPresent){
			DECODE_FIELD(deltaNeutralContract.conId);
			DECODE_FIELD(deltaNeutralContract.delta);
			DECODE_FIELD(deltaNeutralContract.price);
			m_contract->deltaNeutralContract = &deltaNeutralContract;
		}
	}
	return nullptr;
}

char* EOrderDecoder::decodeAlgoParams(const char*& ptr, const char* endPtr) {
	if( m_version >= 21) {
		DECODE_FIELD( m_order->algoStrategy);
		if( !m_order->algoStrategy.empty()) {
			int algoParamsCount = 0;
			DECODE_FIELD( algoParamsCount);
			if( algoParamsCount > 0) {
				TagValueListSPtr algoParams( new TagValueList);
				algoParams->reserve( algoParamsCount);
				for( int i = 0; i < algoParamsCount; ++i) {
					TagValueSPtr tagValue( new TagValue());
					DECODE_FIELD( tagValue->tag);
					DECODE_FIELD( tagValue->value);
					algoParams->push_back( tagValue);
				}
				m_order->algoParams = algoParams;
			}
		}
	}
	return nullptr;
}

char* EOrderDecoder::decodeSolicited(const char*& ptr, const char* endPtr) {
	if (m_version >= 33) {
		DECODE_FIELD( m_order->solicited);
	}
	return nullptr;
}

char* EOrderDecoder::decodeWhatIfInfoAndCommission(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->whatIf);

	decodeOrderStatus(ptr, endPtr);

	if (m_serverVersion >= MIN_SERVER_VER_WHAT_IF_EXT_FIELDS) {
		DECODE_FIELD( m_orderState->initMarginBefore);
		DECODE_FIELD( m_orderState->maintMarginBefore);
		DECODE_FIELD( m_orderState->equityWithLoanBefore);
		DECODE_FIELD( m_orderState->initMarginChange);
		DECODE_FIELD( m_orderState->maintMarginChange);
		DECODE_FIELD( m_orderState->equityWithLoanChange);
	}
	DECODE_FIELD( m_orderState->initMarginAfter);
	DECODE_FIELD( m_orderState->maintMarginAfter);
	DECODE_FIELD( m_orderState->equityWithLoanAfter);
	DECODE_FIELD_MAX( m_orderState->commission);
	DECODE_FIELD_MAX( m_orderState->minCommission);
	DECODE_FIELD_MAX( m_orderState->maxCommission);
	DECODE_FIELD( m_orderState->commissionCurrency);
	DECODE_FIELD( m_orderState->warningText);
	return nullptr;
}

char* EOrderDecoder::decodeOrderStatus(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_orderState->status);
	return nullptr;
}

char* EOrderDecoder::decodeVolRandomizeFlags(const char*& ptr, const char* endPtr) {
	if (m_version >= 34) {
		DECODE_FIELD( m_order->randomizeSize);
		DECODE_FIELD( m_order->randomizePrice);
	}
	return nullptr;
}

char* EOrderDecoder::decodePegBenchParams(const char*& ptr, const char* endPtr) {
	if (m_serverVersion >= MIN_SERVER_VER_PEGGED_TO_BENCHMARK) {
		if (m_order->orderType == "PEG BENCH") {
			DECODE_FIELD( m_order->referenceContractId);
			DECODE_FIELD( m_order->isPeggedChangeAmountDecrease);
			DECODE_FIELD( m_order->peggedChangeAmount);
			DECODE_FIELD( m_order->referenceChangeAmount);
			DECODE_FIELD( m_order->referenceExchangeId);
		}
	}
	return nullptr;
}

char* EOrderDecoder::decodeConditions(const char*& ptr, const char* endPtr) {
	if (m_serverVersion >= MIN_SERVER_VER_PEGGED_TO_BENCHMARK) {

		int conditionsSize;

		DECODE_FIELD( conditionsSize);

		if (conditionsSize > 0) {
			for (; conditionsSize; conditionsSize--) {
				int conditionType;

				DECODE_FIELD( conditionType);

				std::shared_ptr<OrderCondition> item = std::shared_ptr<OrderCondition>(OrderCondition::create((OrderCondition::OrderConditionType)conditionType));

				if (!(ptr = item->readExternal(ptr, endPtr)))
					return 0;

				m_order->conditions.push_back(item);
			}

			DECODE_FIELD( m_order->conditionsIgnoreRth);
			DECODE_FIELD( m_order->conditionsCancelOrder);
		}
	}
	return nullptr;
}

char* EOrderDecoder::decodeAdjustedOrderParams(const char*& ptr, const char* endPtr) {
	if (m_serverVersion >= MIN_SERVER_VER_PEGGED_TO_BENCHMARK) {
		DECODE_FIELD( m_order->adjustedOrderType);
		DECODE_FIELD( m_order->triggerPrice);
		decodeStopPriceAndLmtPriceOffset(ptr, endPtr);
		DECODE_FIELD( m_order->adjustedStopPrice);
		DECODE_FIELD( m_order->adjustedStopLimitPrice);
		DECODE_FIELD( m_order->adjustedTrailingAmount);
		DECODE_FIELD( m_order->adjustableTrailingUnit);
	}
	return nullptr;
}

char* EOrderDecoder::decodeStopPriceAndLmtPriceOffset(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->trailStopPrice);
	DECODE_FIELD( m_order->lmtPriceOffset);
	return nullptr;
}

char* EOrderDecoder::decodeSoftDollarTier(const char*& ptr, const char* endPtr) {
	if (m_serverVersion >= MIN_SERVER_VER_SOFT_DOLLAR_TIER) {
		std::string name, value, displayName;

		DECODE_FIELD( name);
		DECODE_FIELD( value);
		DECODE_FIELD( displayName);

		m_order->softDollarTier = SoftDollarTier(name, value, displayName);
	}
	return nullptr;
}

char* EOrderDecoder::decodeCashQty(const char*& ptr, const char* endPtr) {
	if (m_serverVersion >= MIN_SERVER_VER_CASH_QTY) {
		DECODE_FIELD_MAX( m_order->cashQty);
	}
	return nullptr;
}

char* EOrderDecoder::decodeDontUseAutoPriceForHedge(const char*& ptr, const char* endPtr) {
	if (m_serverVersion >= MIN_SERVER_VER_AUTO_PRICE_FOR_HEDGE) {
		DECODE_FIELD( m_order->dontUseAutoPriceForHedge);
	}
	return nullptr;
}

char* EOrderDecoder::decodeIsOmsContainer(const char*& ptr, const char* endPtr) {
	if (m_serverVersion >= MIN_SERVER_VER_ORDER_CONTAINER) {
		DECODE_FIELD( m_order->isOmsContainer);
	}
	return nullptr;
}

char* EOrderDecoder::decodeDiscretionaryUpToLimitPrice(const char*& ptr, const char* endPtr) {
	if (m_serverVersion >= MIN_SERVER_VER_D_PEG_ORDERS) {
		DECODE_FIELD( m_order->discretionaryUpToLimitPrice);
	}
	return nullptr;
}

char* EOrderDecoder::decodeAutoCancelDate(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->autoCancelDate);
	return nullptr;
}

char* EOrderDecoder::decodeFilledQuantity(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->filledQuantity);
	return nullptr;
}

char* EOrderDecoder::decodeRefFuturesConId(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->refFuturesConId);
	return nullptr;
}

char* EOrderDecoder::decodeAutoCancelParent(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->autoCancelParent);
	return nullptr;
}

char* EOrderDecoder::decodeShareholder(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->shareholder);
	return nullptr;
}

char* EOrderDecoder::decodeImbalanceOnly(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->imbalanceOnly);
	return nullptr;
}

char* EOrderDecoder::decodeRouteMarketableToBbo(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->routeMarketableToBbo);
	return nullptr;
}

char* EOrderDecoder::decodeParentPermId(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_order->parentPermId);
	return nullptr;
}

char* EOrderDecoder::decodeCompletedTime(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_orderState->completedTime);
	return nullptr;
}

char* EOrderDecoder::decodeCompletedStatus(const char*& ptr, const char* endPtr) {
	DECODE_FIELD( m_orderState->completedStatus);
	return nullptr;
}

char* EOrderDecoder::decodeUsePriceMgmtAlgo(const char*& ptr, const char* endPtr) {
	if (m_serverVersion >= MIN_SERVER_VER_PRICE_MGMT_ALGO) {
		DECODE_FIELD((int&)m_order->usePriceMgmtAlgo);
	}
	return nullptr;
}
